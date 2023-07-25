#ifndef _FDEVENT_H_ 
#define _FDEVENT_H_

#include <memory>
#include <functional>
#include <sys/socket.h>
#include <sys/epoll.h>
#include <unistd.h>
#include <vector>

#include "../coroutine/coroutine.h"
#include "../LOCK/lock.h"

class Reactor;

// std::enable_shared_from_this<FdEvent>继承share_from_this函数获取指向自身的shared_ptr
class FdEvent : public std::enable_shared_from_this<FdEvent> {
private:
    
    int m_fd;
    epoll_event m_event;

    Coroutine * m_coroutine;

    Reactor * m_reactor;
public:
    enum IOEvent {
        READ = EPOLLIN,
        WRITE = EPOLLOUT,
        ETmod = EPOLLET,
    };
    typedef std::shared_ptr<FdEvent> FdEventptr;

    std::function<void()> m_read_callback;
    std::function<void()> m_write_callback;

    FdEvent(int fd);
    
    ~FdEvent();
    // 设置回调函数
    void set_callback(IOEvent tag,std::function<void()> cb); 
    // 设置非阻塞模式
    void set_noblock(); 
    // 将fd从epoll移除
    // void del_fd();

    void set_fd(int fd);

    // void set_epoll(int epoll);

    void update_event(int event);

    int get_fd();

    epoll_event& get_event();

    void set_event(bool in,bool ET,bool oneshot);

    void set_event(const epoll_event &ep);

    void set_coroutine(Coroutine *cor);

    Coroutine *get_coroutine(); 

    void set_Reactor(Reactor *reactor);

    Reactor *get_Reactor(); 
};  


class FdPool {
private:
    std::vector<std::pair<FdEvent::FdEventptr,bool>> m_pool;

    int m_size;
    
    Locker m_lock;
    // static FdPool * m_instance;
    FdPool();

public:
    static FdPool * get_instance();

    FdEvent::FdEventptr get_fd();

    void init(int size);

    void re_fd(FdEvent::FdEventptr);
};


#endif