/*
* @brief 内存池
*内存池，用于对应一个协程池
*根据协程池的要求开辟一块内存然后将内存分成很多的块用于协程池的协程栈使用
*/ 
#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <vector>
#include "../LOCK/lock.h"
#include <memory>

class Memory {
private:
    int m_size;
    int m_stack_size;
    int m_total_size;
    int m_unuse_block; // 未被使用的块
    char *m_begin; // 内存开始 
    char *m_end; // 内存结束

    Locker m_lock;
    std::vector<bool> m_using; // 当前的块是否被使用

public:

    using Memoryptr = std::shared_ptr<Memory>;

    Memory(int size, int stack_size);
    ~Memory();

    bool clear_block(int i);

    char *get_block();
    
    bool has_block(char *p); // 地址是否在当前memory之中 
};

#endif