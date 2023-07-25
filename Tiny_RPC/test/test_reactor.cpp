#include "../net/Reactor.h"
#include "../net/Accept.h"
#include "../coroutine/coroutine_pool.h"
#include "../config/Config.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>

void tcpserver_func(int fd) {
    int n = 10;
    while(n >0) {
        char buf[1024];
        int re = read(fd,buf,sizeof(buf));
        std::cout << buf << std::endl;
        strcpy(buf,"tcpserver send!"); 
        n--;
    }

}

int main() {
    Config config("tcpserver","../logs/tcpserver/",1000,100,1024 * 128,10,4999);
    config.set_io_func(tcpserver_func);
    config.start();
}