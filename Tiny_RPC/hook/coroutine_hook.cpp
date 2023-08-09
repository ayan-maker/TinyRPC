#include "coroutine_hook.h"

// 将fdp 修改事件到epoll 中进行监听 0为读
void to_epoll(int fd, int rw) {
    Reactor *tmp = Reactor::get_main_reactor();
    assert(tmp != nullptr);
    if(!tmp->find_fd(fd)) {
        ErrorLog << "fd is not in this Reactor";
        exit(1);
    }
    epoll_event event;
    memset(&event,0,sizeof(event));
    event.data.fd = fd;
    if(rw == 0) { // 读 
        event.events |= EPOLLIN | EPOLLET;
    } else {
        event.events |= EPOLLOUT | EPOLLET;
    }
    tmp->mod_fdevent(fd,event);
}

// 将fd 事件置空
void out_epoll(int fd) {
    Reactor *tmp = Reactor::get_main_reactor();
    assert(tmp != nullptr);
    if(!tmp->find_fd(fd)) {
        ErrorLog << "fd is not in this Reactor";
        exit(1);
    }
    epoll_event event;
    memset(&event,0,sizeof(event));
    event.data.fd = fd;
    tmp->mod_fdevent(fd,event);
}

bool g_hook_enabled = false;

typedef ssize_t (*read_fun_ptr_t)(int fd,void *buf,size_t buflen);

typedef ssize_t (*write_fun_ptr_t)(int fd, const void *buf, size_t count);

typedef int (*accept_fun_ptr_t)(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

// 获取到原系统函数的符号 展开就是read_fun_ptr_t g_sys_read_fun = (read_fun_ptr_t)dlsym(RTLD_NEXT, "read");
#define HOOK_SYS_FUNC(name) name##_fun_ptr_t g_sys_##name##_fun = (name##_fun_ptr_t)dlsym(RTLD_NEXT, #name);

// 相当于先找到系统原本的read函数，然后将其赋给g_sys_read_fun指针
HOOK_SYS_FUNC(read); // read_fun_ptr_t g_sys_read_fun = (read_fun_ptr_t)dlsym(RTLD_NEXT, "read");
HOOK_SYS_FUNC(write);
HOOK_SYS_FUNC(accept);

ssize_t hook_read(int fd,void *buf,size_t buflen) {
    
    // 表示是主协程到达这里，类似于epoll函数跳转到这里
    if(Coroutine::is_main_cor()) { 
        return g_sys_read_fun(fd,buf,buflen);
    }
    
    int n = g_sys_read_fun(fd, buf, buflen);
    // 说明已经有数据了，这里不需要等待异步直接有数据直接退出
    if(n > 0) { 
        return n; 
    }

    // 将fdp 修改事件到epoll 中进行监听
    to_epoll(fd, 0);
    
    Coroutine::Yield(); // 唤醒主协程 

    out_epoll(fd);
    // 再次唤醒
    DebugLog << "read hook func end";
    return g_sys_read_fun(fd, buf, buflen);

}

ssize_t hook_write (int fd, const void *buf, size_t buflen) {
    if(Coroutine::is_main_cor()) { 
        return g_sys_write_fun(fd,buf,buflen);
    }

    // Reactor *tmp = Reactor::get_main_reactor();
    // assert(tmp != nullptr);

    int n = g_sys_write_fun(fd, buf, buflen);
    // 说明已经有数据了，这里不需要等待异步直接有数据直接退出
    if(n > 0) { 
        return n; 
    }

    // 申请fd 将fd放进reactor中
    to_epoll(fd,1);

    Coroutine::Yield(); 

    out_epoll(fd);
    DebugLog << "write hook fun end";
    return g_sys_write_fun(fd,buf,buflen);
}

int hook_accept (int fd, struct sockaddr *addr, socklen_t *addrlen) {
    if(Coroutine::is_main_cor()) { 
        return g_sys_accept_fun(fd,addr,addrlen);
    }

    // Reactor *tmp = Reactor::get_main_reactor();
    // assert(tmp != nullptr);

    int n = g_sys_accept_fun(fd, addr, addrlen);
    // 说明已经有数据了，这里不需要等待异步直接有数据直接退出
    if(n > 0) { 
        return n; 
    }

    // to_epoll(fd,0);

    Coroutine::Yield();

    // tmp->del_fdevent(fdp);

    // out_epoll(fd);

    DebugLog << "accept hook func end";

    return g_sys_accept_fun(fd, addr, addrlen);
}

extern "C" {
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
        if(g_hook_enabled) {
            return hook_accept(sockfd, addr, addrlen);
        }
        return g_sys_accept_fun(sockfd, addr, addrlen);
    }

    ssize_t read(int fd, void *buf, size_t count) {
        if(g_hook_enabled) {
            return hook_read(fd, buf, count);
        }
        return g_sys_read_fun(fd, buf, count);
    }

    ssize_t write(int fd, const void *buf, size_t count) {
        if(g_hook_enabled) {
            return hook_write(fd, buf, count);
        }
        return g_sys_write_fun(fd, buf, count);
    }
}

