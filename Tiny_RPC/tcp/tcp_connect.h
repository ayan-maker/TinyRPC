/*
* TCP连接，用于tcp数据的接收和发送
*/

#ifndef _TCP_CONNECT_H_
#define _TCP_CONNECT_H_

#include <memory>

#include "../net/Reactor.h"
#include "../net/Accept.h"


class Tcp_connect {
public:


private:
    Reactor * m_reactor;
    
};

#endif