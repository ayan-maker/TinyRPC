#include "../coroutine/coroutine.h"
#include <iostream>
#include <unistd.h>
#include "../coroutine/coroutine_pool.h"
#include "../Log/Log.h"
// #include "../net/Reactor.h"

void func1() {
    for(int i=0; i< 10; i++) {
        if(i==5) {
            Coroutine::Yield();
        }
        std::cout<<"i: "<<i<<std::endl;
        usleep(10000);
    }
}


int main () {
    
    AsyncLogger::AsyncLoggerptr Logger(AsyncLogger::get_instance());
    Logger->init("rpc","../logs/",1000);
    Coroutine_pool * pool = Coroutine_pool::get_instance();
    pool->init(10);
    Coroutine::Coroutineptr cor = pool->get_coroutine();
    cor->set_callback_func(func1);

    
    for(int i=0; i< 26; i++) {
        if(i==10 || i==20) {
            Coroutine::Resume(cor.get());
        }
        std::cout<<"i: "<<('a'+i)<<std::endl;
        usleep(10000);
    }


}