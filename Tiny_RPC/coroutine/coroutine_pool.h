/*
*  @brief 协程池
*   用于管理协程 以及协程所需的协程栈空间，
*/

#ifndef _COROUTINE_POOL_H_
#define _COROUTINE_POOL_H_

#include "coroutine.h"
#include <vector>
#include "memory.h"
#include "../LOCK/lock.h"

class Coroutine_pool {
private:
    int m_size; // 协程池的大小
    int m_stack_size; // 协程的栈大小
    int m_free_cor;

    Locker m_lock;

    // Memory::Memoryptr m_memory;

    std::vector<Memory::Memoryptr> m_mem_set; // 用于随时扩充协程

    std::vector<std::pair<Coroutine::Coroutineptr,bool>> m_cor_set; // 
    
    Coroutine_pool();

    static Coroutine_pool * m_instance;

    static Locker m_instance_lock;
public:

    using Corpoolptr = std::shared_ptr<Coroutine_pool>;

    static Coroutine_pool * get_instance();

    void init(int size ,int stack_size = 1024 * 128);

    ~Coroutine_pool();

    // 从协程池中获得一个协程
    Coroutine::Coroutineptr get_coroutine();

    // 将用完的协程重新放回
    void re_coroutine(Coroutine::Coroutineptr cor);

};

#endif