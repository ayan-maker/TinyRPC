#ifndef _COROUTINE_HOOK_H_
#define _COROUTINE_HOOK_H_

#include "coroutine.h"
#include <sys/epoll.h>
#include <unistd.h>
#include <dlfcn.h>
#include <iostream>
#include <assert.h>
#include "../net/Reactor.h"
#include "../net/FdEvent.h"

bool g_hook_enabled = false;

typedef ssize_t (*read_fun_ptr_t)(int fd,void *buf,size_t buflen);


// 获取到原系统函数的符号 展开就是read_fun_ptr_t g_sys_read_fun = (read_fun_ptr_t)dlsym(RTLD_NEXT, "read");
#define HOOK_SYS_FUNC(name) name##_fun_ptr_t g_sys_##name##_fun = (name##_fun_ptr_t)dlsym(RTLD_NEXT, #name);

// 相当于先找到系统原本的read函数，然后将其赋给g_sys_read_fun指针
HOOK_SYS_FUNC(read); // read_fun_ptr_t g_sys_read_fun = (read_fun_ptr_t)dlsym(RTLD_NEXT, "read");


ssize_t hook_read(int fd,void *buf,size_t buflen); 



#endif