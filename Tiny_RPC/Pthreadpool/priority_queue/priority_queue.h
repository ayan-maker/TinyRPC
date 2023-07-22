#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <queue>
#include <functional>
#include <list>
#include "../../LOCK/lock.h"

struct Task {
    std::function<void()> func;
    int priority;
    template<typename Func, typename... Args>
    Task(Func&& fun_t ,Args&&... arge)
    :func(std::bind(std::forward<Func>(fun_t),std::forward<Args>(arge)...)){}

};

class Priority_queue {
private:
    std::queue<Task*> first_queue;
    std::queue<Task*> second_queue;
    std::queue<Task*> thrid_queue;

    int m_queue_size;  // 记录队列的最大容量
    int m_first_num;  // 记录当前队列的任务书
    int m_second_num;
    int m_thrid_num;
    int m_num;        // 当前队伍中的总任务数
    // std::list<Task*>::iterator first_p; // 定位secon队列中的上级任务表
    // std::list<Task*>::iterator second_p;

    Locker m_lock;

    void add_task1(Task* task);
    void add_task2(Task* task);
    void add_task3(Task* task);

public:
    Priority_queue(int n);
    void add_task(Task *task,int priority);
    int re_num() const;
    Task *pop_task();
    bool empty() const;
};

#endif