#include "coroutine_pool.h"

Coroutine_pool * Coroutine_pool::m_instance;
 
Locker Coroutine_pool::m_instance_lock;

Coroutine_pool::Coroutine_pool(){
    
}

void Coroutine_pool::init(int size , int stack_size) {
    m_size = size;
    m_stack_size = stack_size;

    m_mem_set.push_back(std::shared_ptr<Memory>(new Memory(m_size,m_stack_size)));
    
    Memory::Memoryptr t = m_mem_set[0];

    for(int i = 0; i < m_size; i++) { // 将每个协程初始化
        Coroutine::Coroutineptr cor = std::shared_ptr<Coroutine>(new Coroutine(m_stack_size,t->get_block()));
        m_cor_set.push_back(make_pair(cor,false));
    }
    m_free_cor = m_size;

}

Coroutine_pool::~Coroutine_pool() {
    
}

Coroutine::Coroutineptr Coroutine_pool::get_coroutine() {
    
    m_lock.lock();
    // 还有空闲的线程
    if(m_free_cor > 0) {
        for(int i = 0; i<m_cor_set.size(); i++) {
            if(m_cor_set[i].second == false) {
                m_cor_set[i].second = true;
                m_lock.unlock();
                m_cor_set[i].first->set_indx(i);
                return m_cor_set[i].first;
            }
        }
    }
    // 表示没有空闲的协程了
    Memory::Memoryptr tmp = std::shared_ptr<Memory>(new Memory(m_size,m_stack_size));
    Coroutine::Coroutineptr cor = std::shared_ptr<Coroutine>(new Coroutine(m_stack_size,tmp->get_block()));
    cor->set_indx(m_cor_set.size());
    m_cor_set.push_back(make_pair(cor,true));
    for(int i = 1; i < m_size; i++) { // 将每个协程初始化
        Coroutine::Coroutineptr cor = std::shared_ptr<Coroutine>(new Coroutine(m_stack_size,tmp->get_block()));
        m_cor_set.push_back(make_pair(cor,false));
    }
    m_free_cor +=m_size-1;
    m_mem_set.push_back(tmp);
    m_lock.unlock();
    return cor;
}

void Coroutine_pool::re_coroutine(Coroutine::Coroutineptr cor) {
    int t = cor->re_indx();
    m_lock.lock();
    m_cor_set[t].second = false;
    m_free_cor++;
    m_lock.unlock();
    
}

Coroutine_pool* Coroutine_pool::get_instance() {
    if(m_instance == nullptr) {
        m_instance_lock.lock();
        if(m_instance == nullptr) {
            m_instance = new Coroutine_pool;
        }
        m_instance_lock.unlock();
    }
    return m_instance;
}