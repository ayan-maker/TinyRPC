#include <unistd.h>
#include <sys/syscall.h>
#include <assert.h>
#include "../coroutine/coroutine.h"
#include "Log.h"

static thread_local pid_t g_tid = 0;
static pid_t g_pid = 0;

pid_t get_tid() {
    if(g_tid == 0) {
        g_tid = syscall(SYS_gettid);
    }
    return g_tid;
}

LogLevel string_to_LogLevel(const std::string& str) {
    if (str == "DEBUG")
      return LogLevel::DEBUG;
    
    if (str == "INFO")
      return LogLevel::INFO;

    if (str == "WARN")
      return LogLevel::WARN;

    if (str == "ERROR")
      return LogLevel::ERROR;

    if (str == "NONE")
      return LogLevel::NONE;

    return LogLevel::DEBUG;
}

std::string LogLevel_to_string(LogLevel level) {
    std::string re = "DEBUG";
    switch(level) {
        case DEBUG:
            re = "DEBUG";
            return re;
        
        case INFO:
            re = "INFO";
            return re;

        case WARN:
            re = "WARN";
            return re;

        case ERROR:
            re = "ERROR";
            return re;
        
        case NONE:
            re = "NONE";

        default:
            return re;
    }
}

LogEvent::LogEvent(LogLevel level,const char *file_name, int line):m_level(level),m_file_name(file_name),m_line(line){}

LogEvent::~LogEvent(){

}

std::stringstream& LogEvent::get_stringstream() {

    gettimeofday(&m_time,nullptr);

    struct tm time;
    localtime_r(&(m_time.tv_sec),&time);

    const char *format = "%Y-%m-%d %H:%M:%S";
    char buf[128];
    strftime(buf, sizeof(buf),format,&time);
    m_str_stream << "[" << buf << "." << m_time.tv_usec << "]\t"; // \t 制表符 用于垂直对齐

    std::string str = LogLevel_to_string(m_level);
    m_str_stream << "[" << str << "]\t";

    if(g_pid == 0) {
        g_pid = getpid();
    }
    m_pid = g_pid;

    m_tid = get_tid();

    m_cor_id = Coroutine::GetCoroutine()->re_corid();

    m_str_stream << "[ pid :" << m_pid << "]\t" \
                << "[ tid :" << m_tid << "]\t" \
                << "[ corid :" << m_cor_id << "]\t" \
                << "[ file :" << m_file_name << " : "<< m_line << "]\t";

    
    return m_str_stream;
    
}

void LogEvent::log() {
    m_str_stream << "\n";
    AsyncLogger * log = AsyncLogger::get_instance();
    log->push_tack(m_str_stream.str());
} 

Logtmp::Logtmp(LogEvent::LogEventptr event): m_event(event) {

}

Logtmp::~Logtmp() {
    m_event->log();
}

std::stringstream& Logtmp::get_stringstream() {
    m_event->get_stringstream();
}

AsyncLogger* AsyncLogger::m_instance = nullptr;

Locker AsyncLogger::m_instance_lock;

AsyncLogger::AsyncLogger() {
    
}

void AsyncLogger::init(const char* name, const char* path,int maxsize) {
    m_file_name = name;
    m_file_path = path;
    m_max_size = maxsize;

    m_running = true;
    int ret = pthread_create(&m_thread,nullptr,&AsyncLogger::excute,this);
    assert(ret == 0);

}

AsyncLogger* AsyncLogger::get_instance() {
    if(m_instance == nullptr) {
        m_instance_lock.lock();
        if(m_instance == nullptr) {
            m_instance = new AsyncLogger; 
        }
        m_instance_lock.unlock();
    }
    return m_instance;
}

AsyncLogger::~AsyncLogger() {
    stop();
    if(m_file) {
        fclose(m_file);
        m_file = nullptr;
    }
    
    pthread_join(m_thread,nullptr);
}

void AsyncLogger::push_tack(std::string msg) {
    m_lock.lock();
    m_task.push(msg);
    m_lock.unlock();
    m_cond.signal();
}

void AsyncLogger::flush() {
    if(m_file) {
        fflush(m_file);
    }
}

void AsyncLogger::stop() {
    
    if(m_running) {
        m_running = false;
    }
    m_cond.signal();
}

void *AsyncLogger::excute(void *arg)  {
    AsyncLogger *logger = reinterpret_cast<AsyncLogger *>(arg);


    while(logger->m_running) {
        // 取出日志内容
        logger->m_lock.lock();

        while(logger->m_task.empty() && logger->m_running == true) {
            logger->m_cond.wait(logger->m_lock.get());
        }
        std::queue<std::string> tmp;
        tmp.swap(logger->m_task);
        logger->m_lock.unlock();

        // 打开文件
        struct timeval time_val;
        gettimeofday(&time_val, nullptr);

        struct tm time;
        localtime_r(&time_val.tv_sec,&time);

        const char *format = "%Y-%m-%d";
        char namebuf[128];
        strftime(namebuf, sizeof(namebuf),format,&time);
        if(logger->m_file == nullptr) { // 第一次打开
            logger->m_day = namebuf;
            std::string full_name = std::string(logger->m_file_path) + logger->m_file_name + "_" +  logger->m_day + "_" + ("0" + logger->m_no)+ ".log";

            logger->m_file = fopen(full_name.c_str(),"a");
            assert(logger->m_file != nullptr);
        }
        else if(std::string(namebuf) != logger->m_day) { // 表示隔天了
                logger->m_day = namebuf;
                logger->m_size = 0;
                logger->m_no = 0;
                std::string full_name = std::string(logger->m_file_path) + logger->m_file_name + "_" +  logger->m_day + "_" + ("0" + logger->m_no)+ ".log";
                
                fclose(logger->m_file);
                logger->m_file = fopen(full_name.c_str(),"a");
                assert(logger->m_file != nullptr);
        }
        else if(logger->m_size == logger->m_max_size) { // 一个文档写满了
            fclose(logger->m_file);
            logger->m_size = 0;
            logger->m_no++;
            std::string full_name = std::string(logger->m_file_path) + logger->m_file_name + "_" +  logger->m_day + "_" + ("0" + logger->m_no)+ ".log";

            logger->m_file = fopen(full_name.c_str(),"a");
            assert(logger->m_file != nullptr);
        }

        while(!tmp.empty()) {
            fwrite(tmp.front().c_str(),1,tmp.front().size(),logger->m_file);
            tmp.pop();
        }
        logger->flush();
        if(!logger->m_running) {
            break;
        }

    }

    if(logger->m_file) {
        fclose(logger->m_file);
        logger->m_file = nullptr;
    }

}