
#include <assert.h>
#include <iostream>
#include <string.h>
#include "../Log/Log.h"
#include "coroutine.h"

extern "C" {
    extern void coctx_swap(Coctx_t *,Coctx_t *) asm ("coctx_swap");
};

void CoFunction(Coroutine * cor) {
    if(cor) {
        cor->m_callback_func(); // 调用callback函数返回
    }

    Coroutine::Yield();
}

thread_local Coroutine * Coroutine::main_coroutine = nullptr;

thread_local Coroutine * Coroutine::sub_coroutine = nullptr;

int Coroutine::g_coroutine_count =0;
int Coroutine::g_coroutine_id = 0;

Coroutine::Coroutine(int size, char *stack): m_stack_size(size),m_stack_ptr(stack) {
    if(main_coroutine == nullptr) {
        main_coroutine = new Coroutine();
    }
    assert(main_coroutine);
    // 开辟空间

    char *top = m_stack_ptr+m_stack_size; // 指向栈顶

    // 因为64操作系统的机器字长为8所以地址能被8整除，也就是最后4位为0
    top = reinterpret_cast<char *>((reinterpret_cast<unsigned long>(top)) & -16LL);

    // 将内存和寄存器对应起来
    memset(&m_coctx,0,sizeof(m_coctx));
    m_coctx.regs[kRSP] = top;
    m_coctx.regs[kRBP] = top;
    m_coctx.regs[kRETAddr] = reinterpret_cast<char *>(&CoFunction);
    m_coctx.regs[kRDI] = reinterpret_cast<char *>(this);

    // m_id = g_coroutine_id++;
    // g_coroutine_count++;

    // std::cout << "coroutine id: ("<<m_id<<")"<<std::endl;
    InfoLog << "coroutine id: ("<<m_id<<")";
}

Coroutine::Coroutine(int size , char *stack,std::function<void()> callback_func):m_stack_size(size),m_stack_ptr(stack),m_callback_func(callback_func){
    // 如果没有主协程，创建主协程
    if(main_coroutine == nullptr) {
        main_coroutine = new Coroutine();
    }
    assert(main_coroutine);
    // 开辟空间

    char *top = m_stack_ptr+m_stack_size; // 指向栈顶

    // 因为64操作系统的机器字长为8所以地址能被8整除，也就是最后4位为0
    top = reinterpret_cast<char *>((reinterpret_cast<unsigned long>(top)) & -16LL);

    // 将内存和寄存器对应起来
    memset(&m_coctx,0,sizeof(m_coctx));
    m_coctx.regs[kRSP] = top;
    m_coctx.regs[kRBP] = top;
    m_coctx.regs[kRETAddr] = reinterpret_cast<char *>(&CoFunction);
    m_coctx.regs[kRDI] = reinterpret_cast<char *>(this);

    m_id = g_coroutine_id++;
    g_coroutine_count++;

    // std::cout << "coroutine id: ("<<m_id<<")"<<std::endl;
    InfoLog << "coroutine id: ("<<m_id<<")";
}

Coroutine::Coroutine(const Coroutine& other) {
    m_id = other.m_id;
    m_indx= other.m_indx;
    m_coctx = other.m_coctx;
    m_stack_size = other.m_stack_size;
    m_stack_ptr = other.m_stack_ptr;
}
  
Coroutine::~Coroutine() {
    if(m_stack_ptr) {
        delete m_stack_ptr;
    }
    
}

Coroutine::Coroutine() {

    m_id = g_coroutine_id++;
    g_coroutine_count++;

    memset(&m_coctx,0,sizeof(m_coctx));

    // m_coctx_size = 14*8;
    // m_coctx_ptr = new char[m_coctx_size];

    main_coroutine = this;
    sub_coroutine = this;

    // std::cout << "main coroutine id: ("<<m_id<<")"<<std::endl;
    InfoLog << "main coroutine id: ("<<m_id<<")";
}

void Coroutine::set_callback_func(std::function<void()> callback_func) {
    m_callback_func.swap(callback_func);
}

void Coroutine::set_indx(int i) {
    m_indx = i;
}

int Coroutine::re_indx() {
    return m_indx;
}

int Coroutine::re_corid() {
    return m_id;
}
// Coctx_t & Coroutine::get_coctx() {
//     return m_coctx;
// }


void Coroutine::Resume(Coroutine * cor) {
    
    if(sub_coroutine != main_coroutine) { // 表示当前有其他的协程在运行
        // std::cout<<"error: other coroutine is already running" <<std::endl;
        ErrorLog << "error: other coroutine is already running" ;
        return;

    }
    if(main_coroutine == nullptr) {
        // std::cout<<"error:main_coroutine is null"<<std::endl;
        ErrorLog << "error:main_coroutine is null" ;
        return;
    }
    if(cor == nullptr) {
        // std::cout<<"error:coroutine is null"<<std::endl;
        ErrorLog << "error:coroutine is null" ;
        return;
    }
    sub_coroutine = cor;
    coctx_swap(&(main_coroutine->m_coctx), &(cor->m_coctx));
}

void Coroutine::Yield() {
    
    if(main_coroutine == nullptr) {
        // std::cout<<"error:main_coroutine is null"<<std::endl;
        ErrorLog << "error:main_coroutine is null";
        return;
    }
    if(sub_coroutine == nullptr) {
        sub_coroutine = main_coroutine;
        ErrorLog << "error:sub_coroutine is null";
        // std::cout<<"error:sub_coroutine is null"<<std::endl;
        return;
    }
    if(main_coroutine == sub_coroutine) {
        ErrorLog << "error:main_coroutine is sub_coroutine";
        // std::cout<<"error:main_coroutine is sub_coroutine"<<std::endl;
        return;
    }
    Coroutine *tmp = sub_coroutine;
    sub_coroutine = main_coroutine;
    coctx_swap(&(tmp->m_coctx),&(main_coroutine->m_coctx));
    
}

Coroutine * Coroutine::GetCoroutine() {
    if(sub_coroutine == nullptr) {
        sub_coroutine = new Coroutine();
        main_coroutine = sub_coroutine;
    }
    return sub_coroutine;
}

bool Coroutine::is_main_cor() {
    if(main_coroutine == nullptr || main_coroutine == sub_coroutine) {
        return true;
    } 
    return false;
}
