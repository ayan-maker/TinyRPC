#include "memory.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>

Memory::Memory(int size, int stack_size):m_size(size), m_stack_size(stack_size){
    m_total_size = m_size * m_stack_size;
    m_begin = reinterpret_cast<char*>(malloc(m_total_size));
    assert(m_begin != nullptr);
    memset(m_begin, 0, m_total_size);
    m_unuse_block = m_size;
    m_end = m_begin + m_total_size;

    for(int i = 0;i<m_size ;i++) {
        m_using.push_back(false);
    }

}

Memory::~Memory() {
    if(m_begin && m_end) {
        free(m_begin);
    }
}


char *Memory::get_block() {
    
    m_lock.lock();
    if(m_unuse_block == 0) {
        return nullptr;
    }
    char *ans;
    int t = -1;
    for(int i = 0; i < m_size ; i++) {
        if(!m_using[i]) {
            m_using[i] = true;
            m_unuse_block--;
            t = i;
            break;
        }
    }
    m_lock.unlock();
    ans = m_begin+t*m_stack_size;
    return ans;
}

bool Memory::has_block(char *p) {
    if(p<=m_end && p >= m_begin) {
        return true;
    }
    return false;
}

bool Memory::clear_block(int i) {
    if(i >= m_size) {
        return false;
    }
    memset(m_begin+i*m_stack_size,0,m_stack_size);
    return true;
}