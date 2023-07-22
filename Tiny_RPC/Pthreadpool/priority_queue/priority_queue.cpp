#include "priority_queue.h"

Priority_queue::Priority_queue(int n) {
    m_queue_size = n;
    m_first_num = 0;
    m_second_num = 0;
    m_thrid_num = 0;
    m_num = 0;
}

void Priority_queue::add_task(Task* task , int priority) {
    if(priority <= 1) {
        add_task1(task);
    }
    else if(priority ==2) {
        add_task2(task);
    }
    else {
        add_task3(task);
    }
}


void Priority_queue::add_task1(Task* task) {
    m_lock.lock();
    thrid_queue.emplace(task);
    m_thrid_num++;
    m_num++;
    m_lock.unlock();
}

void Priority_queue::add_task2(Task* task) {
    m_lock.lock();
    second_queue.emplace(task);
    m_second_num++;
    m_num++;
    m_lock.unlock();

}

void Priority_queue::add_task3(Task* task) {
    m_lock.lock();
    first_queue.emplace(task);
    m_first_num++;
    m_num++;
    m_lock.unlock();
}

Task *Priority_queue::pop_task() {
    Task *ans = nullptr;
    m_lock.lock();
    if(m_first_num > 0) {
        ans = first_queue.front();
        first_queue.pop();
        m_first_num--;
    }
    else if(m_second_num >0) {
        ans = second_queue.front();
        second_queue.pop();
        m_second_num--;
    }
    else {
        ans = thrid_queue.front();
        thrid_queue.pop();
        m_thrid_num--;
    }
    m_num--;
    m_lock.unlock();
    return ans;
}

bool Priority_queue::empty() const {
    return m_num == 0;
}