#include "Pthreadpool.h"
#include <unistd.h>
#include <tuple>

Pthreadpool::Pthreadpool(int n,int max , int max_task):task_queue(max_task){
    m_thread_num = n;
    m_thread_max = max;
    m_thread_work = 0;
    m_max_task = max_task;
    m_thread_free = m_thread_num;
    m_task = 0;
    exit_num = 0;
    m_thread = new pthread_t[m_thread_max];
    m_end = false;
}

Pthreadpool::~Pthreadpool() {

}

void Pthreadpool::destroy_pool() {
    m_lock.lock();
    while(!task_queue.empty()) {
        Task * task = task_queue.pop_task();
        delete task;
    }
    m_task = 0;
    for(int i = 0; i < m_thread_max ; i++) {
        // 唤醒阻塞的线程
        m_empty_cond.signal();
    }
    delete [] m_thread;
    m_end = true;
    m_lock.unlock();
    pthread_join(m_manager,NULL);
    printf("ending !!!!!!!!\n");
    
}
void Pthreadpool::Init() {

    pthread_create(&m_manager,NULL,manager,this);

    for(int i = 0;i<m_thread_num;i++) {
        pthread_create(&m_thread[i],NULL,worker,this);
    }

}

// 监视线程数量
void Pthreadpool::monitor() {
    // 主要是用于监测线程数量
    // 如果线程数量太少 要增加线程
    while(!m_end) {
        sleep(5);
        m_lock.lock();
        int recent_num = m_task;
        m_lock.unlock();
        if(recent_num > m_thread_num && m_thread_num < m_thread_max) {
            int addn=0;
            if(m_thread_num +CHANGE_NUM > m_thread_max) {
                addn = m_thread_max - m_thread_num;
            }
            else {
                addn = CHANGE_NUM;
            }
            m_lock.lock();
            for(int j =0;j<m_thread_max && addn >0;j++) {
                if(m_thread[j]==0) {
                    printf("create thread \n");
                    pthread_create(&m_thread[j],NULL,worker,this);
                    addn--;
                    
                    m_thread_num++;
                    
                }
            }
            m_lock.unlock();
        }
        // 任务太少，减少线程数量
        if(recent_num*2 < m_thread_num && m_thread_num >= 0) {
            m_lock.lock();
            exit_num = (m_thread_num > CHANGE_NUM )? CHANGE_NUM : m_thread_num;
            m_lock.unlock();
            for(int i = 0; i <CHANGE_NUM && m_thread_num >=0 ; i++) {
                // 提醒等待的线程继续运行，继续运行就会自动释放
                m_empty_cond.signal();
                printf("destroy thread\n");
                
            }
            
        }
    //   
    }
    printf("manager end!!!!!!!!!!!!\n");
}

void Pthreadpool::run() {
    while(1) {
        m_lock.lock();
        
        while(m_task==0) {
            m_empty_cond.wait(m_lock.get());
            if(m_task==0 && exit_num>0) {
                m_thread_num--;
                m_lock.unlock();
                destroy_pth(pthread_self());
            }
        }
        Task *task = task_queue.pop_task();
        m_task--;
        m_full_cond.signal();
        m_lock.unlock();
        task->func();
        delete task;

    }

}

void Pthreadpool::destroy_pth(pthread_t t) {
    m_lock.lock();
    for(int i = 0;i<m_thread_max;i++) {
        if(m_thread[i] == t) {
            m_lock.unlock();
            m_thread[i] = 0;
            pthread_exit(&m_thread[i]);
        }
    }
    
}

// void Pthreadpool::add_task(func_t function,void *arg) {
//     Task *new_task = new Task;
//     new_task->func = function;
//     new_task->args = arg;
//     m_lock.lock();
//     while(m_task == m_max_task) {
//         m_full_cond.wait(m_lock.get());
//     }
//     m_task_queue.emplace(new_task);
//     m_task++;
//     m_empty_cond.signal();
//     m_lock.unlock();
    
// }

// template <typename func,typename... Args>
// void Pthreadpool::add_task(int i,func func_t,Args... args) {
//     Task *new_task = new Task(func_t,args...);
//     m_lock.lock();
//     while(m_task == m_max_task) {
//         m_full_cond.wait(m_lock.get());
//     }
//     task_queue.add_task(new_task);
//     m_task++;
//     m_empty_cond.signal();
//     m_lock.unlock();
// }

template<typename... Args>
std::tuple<Args...> & to_tuple(Args... args) {
    return std::make_tuple<Args...>(std::forward<Args...>(args)...);
}


void* Pthreadpool::manager(void *arg) {
    Pthreadpool *pool = (Pthreadpool*)arg;
    pool->monitor();
}

void* Pthreadpool::worker(void *arg) {
    Pthreadpool *pool = (Pthreadpool*)arg;
    pool->run();
}

Pthreadpool *Pthreadpool::get_instance() {
    static Pthreadpool instance(10,20,200);
    return &instance;
}