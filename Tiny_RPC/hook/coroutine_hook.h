#ifndef _COROUTINE_HOOK_H_
#define _COROUTINE_HOOK_H_

#include "../coroutine/coroutine.h"

#include <sys/epoll.h>
#include <unistd.h>
#include <dlfcn.h>
#include <iostream>
#include <assert.h>

#include "../net/Reactor.h"
#include "../net/FdEvent.h"



ssize_t hook_read(int fd,void *buf,size_t buflen); 

ssize_t hook_write (int fd, const void *buf, size_t buflen);

int hook_accept (int fd, struct sockaddr *addr, socklen_t *addrlen);


extern "C" {

    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

    ssize_t read(int fd, void *buf, size_t count);

    ssize_t write(int fd, const void *buf, size_t count);

}
#endif