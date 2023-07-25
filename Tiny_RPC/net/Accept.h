#ifndef _ACCEPTY_H_
#define _ACCEPTY_H_
/*
* @brief 监听Reactor
*/
#include <vector>
#include "FdEvent.h"
#include "Reactor.h"

class Accept {
private:
    static const int MAX_EVENTS = 1024;
    int m_listenfd;
    int m_workerfd_size; // 工作线程的数量
    int m_port; // 端口号
    int m_epollfd; // epollfd
    int m_closefd; // 用于唤醒
    bool m_running; 

    
    std::vector<std::pair<Reactor *, pthread_t>> m_reactors; // 工作Reactor，每个rector对应一个线程 

    static bool m_listen_run;
    static Locker m_io_lock;

    std::function<void(int)> m_call_back;
public:
    using Acceptptr = std::shared_ptr<Accept>;

    Accept(int size, int port);
    ~Accept();

    void wake_up(int i);

    void loop();
    
    void close_loop();

    void set_call_back(std::function<void(int)>);

    static void* io_pthread_func(void *);

    void read_work(); // 监听工作
};


#endif