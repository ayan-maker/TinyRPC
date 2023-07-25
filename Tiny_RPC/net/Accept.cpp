#include "Accept.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#include <string.h>

#include "../coroutine/coroutine_pool.h"
#include "../hook/coroutine_hook.h"

// extern ssize_t hook_read(int fd,void *buf,size_t buflen); 

// extern ssize_t hook_write (int fd, const void *buf, size_t buflen);

// extern int hook_accept (int fd, struct sockaddr *addr, socklen_t *addrlen);

bool Accept::m_listen_run;

Locker Accept::m_io_lock;

Accept::Accept(int size, int port):m_workerfd_size(size), m_port(port) {
    
    // 1、epoll
    m_epollfd = epoll_create(1);

    // 1、设置监听listenfd
    m_listenfd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_addr.s_addr = htonl(INADDR_ANY); // 主机地址变成网络字节序
    addr.sin_family = AF_INET; // Ip版本
    addr.sin_port = htons(m_port); // 端口号 
    
    int flag = 1;
    setsockopt(m_listenfd, SOL_SOCKET, SO_REUSEADDR,&flag,sizeof(flag)); // 设置socket允许重用本地地址端口

    // 如果 linger 选项被启用，那么在关闭 socket 时，如果还有数据没有发送完成，
    // 操作系统将会等待 l_linger 秒钟，然后强制关闭 socket，这样可以确保数据被发送完整
    struct linger tmp = {1,1};
    setsockopt(m_listenfd,SOL_SOCKET,SO_LINGER,&tmp,sizeof(tmp)); 

    int re = bind(m_listenfd,(sockaddr*)&addr,sizeof(addr));
    if(re != 0) {
        close(m_listenfd);
        m_listenfd = 0;
        ErrorLog << "Error: Failed to bind";
        exit(1);
    }
    re = listen(m_listenfd,10);
    if(re != 0) {
        close(m_listenfd);
        m_listenfd = 0;
        ErrorLog << "Error: Failed to listen()";
        exit(1);
    }

    // 开辟线程
    for(int i = 0; i < m_workerfd_size; i++) {
        pthread_t thread;
        pthread_create(&thread, NULL,io_pthread_func,this);
    }
    // Reactor::set_accept(this);
} 

Accept::~Accept() {
    
    close_loop();
    
}

void * Accept::io_pthread_func(void *arg) {
    Accept *accept = (Accept*)arg;
    Reactor * tmp = Reactor::get_main_reactor();
    m_io_lock.lock();
    accept->m_reactors.push_back(std::make_pair(tmp,pthread_self()));
    m_io_lock.unlock();
    tmp->loop();
}

void Accept::loop() {
    // 屏蔽信号
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask,SIGINT);
    pthread_sigmask(SIG_BLOCK,&mask,nullptr);
    

    // 将监听fd绑到epoll中
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.data.fd = m_listenfd;
    event.events = EPOLLIN | EPOLLET;
    epoll_ctl(m_epollfd,EPOLL_CTL_ADD,m_listenfd,&event);

    m_listen_run = true;

    Coroutine::Coroutineptr cor = Coroutine_pool::get_instance()->get_coroutine();
    std::function<void()> func = std::bind(std::mem_fn(&Accept::read_work),this); // std::mem_fn 适用于将类成员函数转成可执行对象
    cor->set_callback_func(func);
    Coroutine::Resume(cor.get());
    while(m_running) {
        struct epoll_event events[MAX_EVENTS];

        int index = epoll_wait(m_epollfd,events,MAX_EVENTS,900000);

        if(index < 0) {
            ErrorLog << "ERROR: epoll_wait" ;
            perror("epoll_wait");
            exit(1);
        }
        if(index == 0) {
            WarnLog << "epoll_wait outtime" ;
            // std::cout<<"epoll_wait outtime" <<std::endl;
            exit(0);
        }
        for(int i = 0; i < index; i++) {
            if(events[i].data.fd == m_closefd) { // 要关闭loop
                char buf[8];
                read(m_closefd, buf, sizeof(buf));
                break;
            }
            else {
                Coroutine::Resume(cor.get());
            }
        }
    }
}

void Accept::close_loop() {
    m_running = false;
    m_call_back = nullptr;
    for(int i=0;i<m_workerfd_size;i++) {
        m_reactors[i].first->close_loop();
    }
    write(m_closefd,"close",6);
}

void Accept::read_work() {
    while(m_listen_run) {
        int socketfd = hook_accept(m_listenfd,nullptr,0);
        
        int no = socketfd % m_workerfd_size;
        std::shared_ptr<FdEvent> Fd(new FdEvent(socketfd));
        Fd->set_noblock();
        std::function<void()> func = std::function<void()>(std::bind(m_call_back,socketfd));
        m_reactors[no].first->add_func(func);
        m_reactors[no].first->add_fdevent(Fd);
        wake_up(no);
    }
}

void Accept::wake_up(int i) {
    if(i >= m_workerfd_size) {
        ErrorLog << "i exceeds m_workerfd_size";
        exit(1);
    }
    // 唤醒相关的工作线程
    int fd = m_reactors[i].first->re_wake();
    int buf[8];
    hook_write(fd,buf,8);
}

void Accept::set_call_back(std::function<void(int)> func) {
    m_call_back = func;
}