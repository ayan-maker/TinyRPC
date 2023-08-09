#include "Reactor.h"
#include <sys/epoll.h>
#include <iostream>
#include <sys/socket.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/eventfd.h>
#include <signal.h>

#include "../Pthreadpool/Pthreadpool/Pthreadpool.h"
#include "../coroutine/coroutine_pool.h"
#include "../hook/coroutine_hook.h"

thread_local Reactor *Reactor::current_Reactor = nullptr;

Reactor::Reactor() {
    m_fd_count = 0;
    m_id = pthread_self();
    m_epollfd = epoll_create(1);
    m_runing = true;
    if(m_epollfd == -1) {
        ErrorLog << "create epollfd";
        perror("create epollfd");
        exit(1);
    }
    // 设置wakeupfd
    m_wakeupfd = eventfd(0,0);
    if(m_wakeupfd ==-1) {
        ErrorLog << "Error: wakeupfd created failed";
        exit(1);
    }
    struct epoll_event event;
    memset(&event, 0, sizeof(event));
    event.data.fd = m_wakeupfd;
    event.events = EPOLLIN;
    epoll_ctl(m_epollfd,EPOLL_CTL_ADD,m_wakeupfd,&event);

    // 设置closefd
    m_closefd = eventfd(0,0);
    if(m_closefd ==-1) {
        ErrorLog << "Error: m_closefd created failed";
        exit(1);
    }
    memset(&event, 0, sizeof(event));
    event.data.fd = m_closefd;
    event.events = EPOLLIN;
    epoll_ctl(m_epollfd,EPOLL_CTL_ADD,m_closefd,&event);
    // loop();
}

Reactor::~Reactor() {
    // close_loop();
    // usleep(10);
    for(auto i:m_fd_set) {
        delete i.second;
    }
    close(m_epollfd);
    close(m_wakeupfd);
    close(m_closefd);
}

void Reactor::add_fdevent(FdEvent* event) {
    if(m_fd_set.find(event->get_fd()) == m_fd_set.end()) {
        m_fd_set[event->get_fd()] = event;
        epoll_ctl(m_epollfd,EPOLL_CTL_ADD,event->get_fd(),&(event->get_event()));
    } 
    else {
        ErrorLog << "ERROR:fd exists" ;
    }
    
}

void Reactor::add_fdevent(FdEvent::FdEventptr &event) {
    if(m_fd_set.find(event->get_fd()) == m_fd_set.end()) {
        m_fd_set[event->get_fd()] = event.get();
        epoll_ctl(m_epollfd,EPOLL_CTL_ADD,event->get_fd(),&(event->get_event()));
    } 
    else {
        ErrorLog << "ERROR:fd exists" ;
    }
    
}

void Reactor::del_fdevent(FdEvent* event) {
    if(m_fd_set.find(event->get_fd()) != m_fd_set.end()) {
        m_fd_set.erase(event->get_fd());
        epoll_ctl(m_epollfd,EPOLL_CTL_DEL,event->get_fd(),nullptr);
    }
    else {
        ErrorLog << "ERROR: fd not found" ;
    }

}

void Reactor::del_fdevent(FdEvent::FdEventptr &event) {
    if(m_fd_set.find(event->get_fd()) != m_fd_set.end()) {
        m_fd_set.erase(event->get_fd());
        epoll_ctl(m_epollfd,EPOLL_CTL_DEL,event->get_fd(),nullptr);
    }
    else {
        ErrorLog << "ERROR: fd not found" ;
    }
}

void Reactor::mod_fdevent(int fd, epoll_event event) {
    if(m_fd_set.find(fd) == m_fd_set.end()) {
        ErrorLog << "fd is not in this Reactor";
        exit(1);
    }
    FdEvent * t = m_fd_set[fd];
    t->set_event(event);
    epoll_ctl(m_epollfd, EPOLL_CTL_MOD, fd, &(t->get_event()));
}

void Reactor::loop() {
    // 屏蔽信号
    sigset_t mask;
    sigfillset(&mask);
    sigdelset(&mask,SIGINT);
    pthread_sigmask(SIG_BLOCK,&mask,nullptr);

    // 监听事件
    if(m_runing) {
        fd_work();
    }
    
}

void Reactor::add_func(std::function<void()> func) {
    m_peing_func.push(func);
}

// Reactor *Reactor::get_main_reactor() {
//     if(main_Reactor == nullptr) {
//         main_Reactor = new Reactor;
//     }
//     return main_Reactor;
// }

void Reactor::close_loop() {
    m_runing = false;
    write(m_closefd, "close",8); 
}

bool Reactor::find_fd(int fd) {
    if(m_fd_set.find(fd) == m_fd_set.end()) {
        return false;
    }
    return true;
}

int Reactor::re_wake() {
    return m_wakeupfd;
}
// void Reactor::set_type(ReactorType type) {
//     m_type = type;
//     if(m_type == Listener && main_Reactor == nullptr) {
//         main_Reactor = this;
//     }
// }


// void Reactor::listen_work(int port) {

//     m_listenfd = socket(AF_INET, SOCK_STREAM, 0);
//     if(m_listenfd < 0) {
//         ErrorLog << "ERROR: create socket" ;
//         perror("create socket");
//         exit(1);
//     }

    
//     struct sockaddr_in addr;
//     memset(&addr, 0, sizeof(addr));
//     addr.sin_family = AF_INET; // ip协议版本
//     addr.sin_port = htons(port); // 通信端口，将主机字节序转换成网络字节序
//     addr.sin_addr.s_addr = htonl(INADDR_ANY); // 将主机地址转变成网络字节序
//     bind(m_listenfd,(struct sockaddr *)&addr,sizeof(addr));
//     listen(m_listenfd,10);

//     while(m_runing) {
//         epoll_event events[MAX_EVENTS_NUM];

//         int index = epoll_wait(m_epollfd,events,MAX_EVENTS_NUM,900000);

//         if(index < 0) {
//             ErrorLog << "ERROR: epoll_wait" ;
//             perror("epoll_wait");
//             exit(1);
//         }
//         if(index == 0) {
//             WarnLog << "epoll_wait outtime" ;
//             exit(0);
//         }
//         for(int i=0;i<index;i++) {
//             deal_fd();
//         }
//     }
// }

void Reactor::fd_work() {

    while (m_runing) {

        epoll_event events[MAX_EVENTS_NUM];

        int index = 0;
        while((index = epoll_wait(m_epollfd,events,MAX_EVENTS_NUM,900000))==-1 && errno == EINTR);

        if(index < 0) {
            ErrorLog << "ERROR: epoll_wait" << errno ;
            perror("epoll_wait");
            exit(1);
        }
        if(index == 0) {
            WarnLog << "epoll_wait outtime" ;
            // std::cout<<"epoll_wait outtime" <<std::endl;
            exit(0);
        }

        for(int i = 0;i<index;i++) {
            int fdi = events[i].data.fd;
            if(fdi == m_wakeupfd) { // 用于唤醒执行任务
                char buf[8];
                read(events[i].data.fd,buf,sizeof(buf));
                std::queue<std::function<void()>> tmp;
                m_func_lock.lock();
                tmp.swap(m_peing_func);
                m_func_lock.unlock();
                int n = tmp.size();
                for(int i=0; i<n; i++) {
                    Coroutine::Coroutineptr cor = Coroutine_pool::get_instance()->get_coroutine();
                    cor->set_callback_func(tmp.front());
                    Coroutine::Resume(cor.get());
                }
            } else if(events[i].data.fd == m_closefd){ // 结束loop
                char buf[8];
                read(m_closefd,buf,sizeof(buf));
                break;
            
            } else if(events[i].events & (EPOLLIN | EPOLLRDHUP) ) { // fd断开链接

                del_fdevent(m_fd_set[fdi]);
            } else {
                deal_fd(events[i]);
            }
             
        }
    }
}

void Reactor::deal_fd(epoll_event &ev) {
    if(m_fd_set.find(ev.data.fd) == m_fd_set.end()) {
        ErrorLog << "ERROR: fd not found" ;
        perror("fd not found");
        exit(1);
    }
    FdEvent *fd = m_fd_set[ev.data.fd];
    if(fd->get_Reactor() != this) {
        ErrorLog << "ERROR: fd is not belong to this" ;
        perror("fd is not belong to this");
        exit(1);
    }
    // 如果是存在协程，就唤醒协
    if(fd->get_coroutine()!=nullptr) {
        
        Coroutine::Resume(fd->get_coroutine());
    } else {
        ErrorLog << "Error: Coroutine not started";
        perror("Coroutine not started");
    }
    // else {
    //     Pthreadpool *pool =  Pthreadpool::get_instance();
    //     if((!ev.events & EPOLLIN) && (!ev.events & EPOLLOUT)) { // 要删除该fd
    //         pool->add_task(1,[&](){
    //             del_fdevent(fd);
    //         });
    //     }
    //     else if(ev.events & EPOLLIN) {
    //         pool->add_task(1,[&](){
    //             fd->m_read_callback();
    //         });
    //     }
    //     else if(ev.events & EPOLLOUT) {
    //         pool->add_task(1,[&](){
    //             fd->m_write_callback();
    //         });
    //     }
    // }
    
}

Reactor *Reactor::get_main_reactor() {
    if(current_Reactor == nullptr) {
        current_Reactor = new Reactor;
    }
    return current_Reactor;
}