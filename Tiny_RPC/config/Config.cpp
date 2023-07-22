#include "Config.h"

Config::Config(const char*name, const char* path,int log_size, int pool_size, int pool_stack_size,int io_size):\
m_log_name(name),m_log_path(path),m_log_size(log_size),m_pool_size(pool_size),m_pool_stack_size(pool_stack_size),\
m_io_size(io_size) {
    m_Log = AsyncLogger::get_instance();
    m_Log->init(m_log_name,m_log_path,m_log_size);
    m_cor_pool = Coroutine_pool::get_instance();
    m_cor_pool->init(m_pool_size,m_pool_stack_size);
    m_Accept = std::shared_ptr<Accept>(new Accept(io_size));
}

Config::~Config() {

}

void Config::set_io_func(std::function<void(int)> func) {
    m_Accept->set_call_back(func);
}

void Config::start() {
    m_Accept->loop();
}