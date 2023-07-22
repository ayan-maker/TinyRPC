#include "LOCK/lock.h"
#include "Pthreadpool/Pthreadpool.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>

void func(int tmp,int b,int c,int d) {
    printf("treadid : %ld ,arg : %d %d %d %d \n",pthread_self(),tmp,b,c,d);
    sleep(1);
}

void func2(char a,int b,double c) {
    printf("treadid : %ld ,arg : %c %d %d %f \n",pthread_self(),a,b,c);
    sleep(1);
}

int main () {
    Pthreadpool pool(5,20,50);
    pool.Init();
    char c='0';
    for(int i=0;i<100;i++) {
        pool.add_task(3,&func,i,i+1,i+90,i+89);
        usleep(500);
        pool.add_task(i%4,&func2,c++,i+50,(double)(i+90)/2);
    }
    sleep(20);
    pool.destroy_pool();

}