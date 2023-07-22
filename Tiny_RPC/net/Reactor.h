#ifndef _REACTOR_H_
#define _REACTOR_H_

#include "../LOCK/lock.h"
#include "../Log/Log.h"
#include "FdEvent.h"
#include <thread>
#include <map>
#include <queue>
#include <functional>

// one pool per thread + 线程池
// 处理事务的Reactor
class Reactor {
public:
    static  const int MAX_EVENTS_NUM = 1024;
    static thread_local Reactor *current_Reactor; // 每个线程有一个reacter

    // static Accept *main_Reactor; // 主进程用于监听的进程
    
    typedef std::shared_ptr<Reactor> ReactorPtr;

    // enum ReactorType {
    //     Listener = 1,
    //     Worker = 2
    // };

private:
    
    pid_t m_id; // 用线程编号作为表示，每一个线程就一个Reactor
    // int m_reactor_id; // 标识作用
    int m_epollfd; // epollfd
    int m_wakeupfd; // 用于唤醒
    int m_closefd; // 用于结束loop
    // int m_listen_port;
    std::map<int,FdEvent *> m_fd_set;
    int m_fd_count;
    bool m_runing; 
    Locker m_func_lock;
    // ReactorType m_type;  // 该reactor的类型

    std::queue<std::function<void()>> m_peing_func; // 用于保存待运行的函数,这些等待的函数就是将fd注册到epoll上

    // void listen_work(int port); // epoll 作为listen监听存在

    void fd_work(); // 文件事件存在 

    void deal_fd(epoll_event &ev); // 处理文件事件
public:
    
    ~Reactor();
    Reactor();
    void add_fdevent(FdEvent* event);
    void add_fdevent(FdEvent::FdEventptr &event);
    void del_fdevent(FdEvent* event);
    void del_fdevent(FdEvent::FdEventptr &event);
    void loop(); // reactor loop
    void add_func(std::function<void()> func);
    void close_loop();
    
    bool find_fd(int fd);
    // void set_type(ReactorType type);
    void set_listenport(int port);
    int re_wake(); 


    // static void set_accept(Accept *accept);
    static Reactor *get_main_reactor(); // 获得当前的main_reactor

};


#endif