#ifndef _PTHREADPOOL_H_
#define _PTHREADPOOL_H_

#include <pthread.h>
#include <iostream>
#include <queue>
#include "../../LOCK/lock.h"
#include <functional>
#include <tuple>
#include "../priority_queue/priority_queue.h"



class Pthreadpool {
private:
    static const int CHANGE_NUM = 3;
    typedef void (*func_t)(void*);
    int m_thread_num; // 当前的可工作线程数
    int m_thread_max; // 最大的线程数量
    int m_thread_work; // 当前正在工作的线程数量
    int m_thread_free; // 当前空闲的线程数
    int m_task;         // 当前任务队列的任务数
    int m_max_task;
    int exit_num;

    bool m_end;
    
    pthread_t *m_thread; // 线程id
    // std::queue<Task *> m_task_queue;  // 任务队列
    Priority_queue task_queue; 
    pthread_t m_manager;

    Locker m_lock; // 互斥锁
    Cond m_empty_cond; // 条件变量
    Cond m_full_cond;  //
    static void* manager(void *);
    static void* worker(void *);
    void destroy_pth(pthread_t);

    // static Pthreadpool * Instance;

    Pthreadpool(int n,int max,int max_task);


public:
    void monitor(); // 监视工作，管理线程
    void run();     // 工作线程
    // Pthreadpool(int n,int max,int max_task);
    void destroy_pool();
    ~Pthreadpool();
    void Init();

    static Pthreadpool *get_instance();

    template <typename func,typename... Args>
    inline void add_task(int i,func func_t,Args... args) {
        Task *new_task = new Task(func_t,args...);
        m_lock.lock();
        while(m_task == m_max_task) {
            m_full_cond.wait(m_lock.get());
        }
        task_queue.add_task(new_task,i);
        m_task++;
        m_empty_cond.signal();
        m_lock.unlock();
    }


};


#endif
