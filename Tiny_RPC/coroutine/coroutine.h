#ifndef _COROUTINE_
#define _COROUTINE_

#include <functional>
#include <memory>
#include <thread>



enum {
    kRBP = 6,
    kRDI = 7,
    kRSI = 8,
    kRETAddr = 9,
    kRSP = 13
};


// 寄存器块，将14个寄存器存放在其中
struct Coctx_t {
    void *regs[14];
};
/*
r15	0
r14	8
r13	16
r12	24
r9	32
r8	40
rbp	48
rdi	56
rsi	64
RETaddr	72 //返回地址
rdx	80
rcx	88
rbx	96
rsp	104

*/


class Coroutine {
private:
    int m_id; // 协程id，标志一个协程
    int m_indx; // 标记在协程池中的编号
    struct Coctx_t m_coctx; // 协程结构体，记录寄存器的相关数数值
    int m_stack_size; // 记录协程栈空间大小
    char *m_stack_ptr; // 存储协程栈的位置
    
    Coroutine(); // 初始化主协程

public:
    using Coroutineptr = std::shared_ptr<Coroutine>; 
    
    static thread_local Coroutine * main_coroutine; 
    static thread_local Coroutine * sub_coroutine;
    static int g_coroutine_id; // 记录当前的协程编号到了哪里
    static int g_coroutine_count; // 记录当前有多少协程
    
    std::function<void()> m_callback_func; // 协程运行结束返回到该函数中
public:
    
    Coroutine(int size, char *stack);
    Coroutine(int size, char *stack, std::function<void()> callback_func); 
    Coroutine(const Coroutine &other);
    ~Coroutine();
    void set_callback_func(std::function<void()> callback_func);
    void set_indx(int i);
    int re_indx();
    int re_corid();

    // Coctx_t & get_coctx();
    // 唤醒目标协程
    static void Resume(Coroutine * cor);

    // 返回主协程
    static void Yield();

    // 返回当前协程
    static Coroutine * GetCoroutine();

    // 是否是主协程
    static bool is_main_cor();
};


#endif