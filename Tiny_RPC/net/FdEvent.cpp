#include "FdEvent.h"
#include <sys/socket.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>

FdEvent::FdEvent(int fd):m_fd(fd){
    
    memset(&m_event,0,sizeof(m_event));
    m_event.data.fd = m_fd;
}

FdEvent::~FdEvent(){
    if(m_fd > 0) {
        close(m_fd);
    }
}

void FdEvent::set_callback(IOEvent tag,std::function<void()> cb) {
    
    if(tag == READ) {
        m_read_callback = cb;
        return;
    } 
    if(tag == WRITE) {
        m_write_callback = cb;
        return;
    }
}

void FdEvent::set_noblock() {
    if(m_fd < 0) {
        std::cout<<"error: fd is null"<<std::endl;
        return;
    }
    // 找出标志位
    int flag = fcntl(m_fd,F_GETFL,0);
    if(flag & O_NONBLOCK) {
        std::cout<<"fd already is noblock"<<std::endl;
        return;
    }
    fcntl(m_fd,F_SETFL,flag & O_NONBLOCK);
    flag = fcntl(m_fd,F_GETFL,0);
    if(flag & O_NONBLOCK) {
        std::cout<<"fd is set  noblock"<<std::endl;
    }
    else {
        std::cout<<"fd set noblock fail"<<std::endl;
    }
}

// void FdEvent::del_fd() {
//     if(m_fd < 0) {
//         std::cout<<"fd is null" <<std::endl;
//         return;
//     }
//     epoll_ctl(m_epoll,EPOLL_CTL_DEL,m_fd,nullptr);
// }

void FdEvent::set_fd(int fd) {
    m_fd = fd;
}

// void FdEvent::set_epoll(int epoll) {
//     m_epoll = epoll;
// }

int FdEvent::get_fd() {
    return m_fd;
}

epoll_event& FdEvent::get_event() {
    return m_event;
}

void FdEvent::set_event(bool in,bool ET=false,bool oneshot=false) {
    int tag = 0;
    if(in) {
        tag != EPOLLIN;
    }
    else {
        tag != EPOLLOUT;
    }
    if(ET) {
        tag != EPOLLET;
    }
    if(oneshot) {
        tag != EPOLLONESHOT;
    }
    m_event.events = tag;
}

void FdEvent::set_event(const epoll_event &ep) {
    m_event = ep;
}

void FdEvent::set_coroutine(Coroutine *cor) {
    m_coroutine = cor;
} 

Coroutine * FdEvent::get_coroutine() {
    return m_coroutine;
}

void FdEvent::set_Reactor(Reactor *reactor) {
    m_reactor = reactor;
}

Reactor * FdEvent::get_Reactor() {
    return m_reactor;
}


// ----------------------FdPool---------------------------

FdPool * FdPool::get_instance() {
    static FdPool instance;
    return &instance;
}

FdPool::FdPool() {

}

FdEvent::FdEventptr FdPool::get_fd() {
    int t = -1;
    m_lock.lock();
    for(int i=0; i<m_size; i++) {
        if(m_pool[i].second == false) {
            m_pool[i].second = true;
            t=i;
            break;
        }
    }
    m_lock.unlock();
    if(t > -1) {
        return m_pool[t].first;
    }
    return nullptr;
}

void FdPool::init(int size) {
    m_size = size;
}

void FdPool::re_fd(FdEvent::FdEventptr fd) {
    
    for(int i=0; i<m_size; i++) {
        if(m_pool[i].first == fd) {
            m_lock.lock();
            m_pool[i].second = false;
            m_lock.unlock();
            break;
        }
    }
    
}