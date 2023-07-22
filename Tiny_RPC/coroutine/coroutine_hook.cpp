#include "coroutine_hook.h"


ssize_t hook_read(int fd,void *buf,size_t buflen) {
    
    // 表示是主协程到达这里，类似于epoll函数跳转到这里
    if(Coroutine::is_main_cor()) { 
        return g_sys_read_fun(fd,buf,buflen);
    }
    
    // 非主协程中进行的操作
    // 写入监听
    Reactor *tmp = Reactor::get_main_reactor();
    assert(tmp != nullptr);
    
    int n = g_sys_read_fun(fd, buf, buflen);
    // 说明已经有数据了，这里不需要等待异步直接有数据直接退出
    if(n > 0) { 
        return n; 
    }

    // 将fdp 加入到epoll 中进行监听
    std::shared_ptr<FdEvent> fdp(new FdEvent(fd));
    fdp->set_event(true,false,false);
    fdp->set_noblock();
    fdp->set_coroutine(Coroutine::GetCoroutine());
    fdp->set_Reactor(tmp);
    tmp->add_fdevent(fdp); // 将fd加入epoll 中监听
    
    Coroutine::Yield(); // 唤醒主协程

    tmp->del_fdevent(fdp); 

    // 再次唤醒
    return g_sys_read_fun(fd, buf, buflen);

}