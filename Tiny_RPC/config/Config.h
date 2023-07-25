#ifndef _CONFIG_H_
#define _CONFIG_H_
#include "../Log/Log.h"
#include "../coroutine/coroutine_pool.h"
#include "../net/Accept.h"

class Config {
private:
    AsyncLogger* m_Log;
    Coroutine_pool* m_cor_pool;
    Accept::Acceptptr m_Accept;

    // log参数
    const char* m_log_name;
    const char* m_log_path;
    int m_log_size;
    // 协程池参数
    int m_pool_size;
    int m_pool_stack_size;
    // Accept 参数
    int m_io_size;
    int m_port;
public:
    Config(const char*name, const char* path,int log_size, int pool_size, int pool_stack_size,int io_size, int port);
    
    ~Config();

    void set_io_func(std::function<void(int)> func);

    void start();
};


#endif