#ifndef _LOG_H_
#define _LOG_H_

#include <sys/time.h>
#include <string>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <memory>
#include <queue>
#include <pthread.h>
#include "../LOCK/lock.h"

enum LogLevel {
	DEBUG = 1,
	INFO = 2,
	WARN = 3,
	ERROR = 4,
    NONE = 5    // don't print log
};

pid_t get_tid();

LogLevel string_to_LogLevel(const std::string& str);

std::string LogLevel_to_string(LogLevel level);

// 记录每个事件的内容，类似一条语句
class LogEvent {
private:
    struct timeval m_time; // 事件发生的时间
    LogLevel m_level; // 
    pid_t m_pid; // 进程号
    pid_t m_tid; // 线程号
    int m_cor_id; // 协程id

    const char *m_file_name; // 准备写到那个文件
    int m_line;
    std::string m_msg;
    std::stringstream m_str_stream; // string流

public:

    using LogEventptr = std::shared_ptr<LogEvent>;

    LogEvent(LogLevel level,const char *file_name, int line);

    ~LogEvent();

    std::stringstream& get_stringstream(); // 将文案全部送进string流中

    void log(); // 将string流引入到异步队列中
};

// 用于生成logevent 然后再析构时将事件Push到队列中去
class Logtmp {
private:
    LogEvent::LogEventptr m_event;

public:

    explicit Logtmp(LogEvent::LogEventptr event);

    ~Logtmp();

    std::stringstream& get_stringstream();

};

// 异步的日志系统
class AsyncLogger {
private:
    const char* m_file_name;
    const char * m_file_path;
    FILE * m_file;
    int m_max_size; 
    int m_size; // 用于记录当前log记录了多少行日志
    int m_no {0}; // 当天的第几个log
    std::string m_day; // 表示是那一天，用于不同的天记录在不同的log中
    std::queue<std::string> m_task; // 异步日志，先将日志系统放在队列中

    static Locker m_instance_lock; // 用于单例模式上锁
    Locker m_lock;
    Cond m_cond;
    bool m_running;
    bool m_file_open; // 文件是否打开

    pthread_t m_thread; // 用于异步线程

    AsyncLogger();
    
    AsyncLogger(const AsyncLogger& other) = delete;

    AsyncLogger& operator=(const AsyncLogger& other) =delete;

    static AsyncLogger * m_instance;

public:
    using AsyncLoggerptr = std::shared_ptr<AsyncLogger>;

    void init(const char* name, const char* path,int maxsize);
    
    static AsyncLogger *get_instance();

    ~AsyncLogger();

    void push_tack(std::string msg);

    void flush();  // 将缓冲区的内容更新到文件中

    void stop(); // 停止

    static void *excute(void *); // 用于处理文件任务
        
};

// class Loggerinstance {
// private:
//     Loggerinstance(const char* name, const char* path,int maxsize);

//     Loggerinstance& operator=(const Loggerinstance& other);

//     Loggerinstance(const Loggerinstance& other);

// public:

//     static Loggerinstance *get_intance();

    

// };

#define DebugLog \
        Logtmp(std::shared_ptr<LogEvent>(new LogEvent(LogLevel::DEBUG,__FILE__,__LINE__))).get_stringstream()

#define InfoLog \
        Logtmp(std::shared_ptr<LogEvent>(new LogEvent(LogLevel::INFO,__FILE__,__LINE__))).get_stringstream()

#define WarnLog \
        Logtmp(std::shared_ptr<LogEvent>(new LogEvent(LogLevel::WARN,__FILE__,__LINE__))).get_stringstream()

#define ErrorLog \
        Logtmp(std::shared_ptr<LogEvent>(new LogEvent(LogLevel::ERROR,__FILE__,__LINE__))).get_stringstream()


#endif