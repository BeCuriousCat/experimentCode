/*thread_attr.c*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define REPEAY_NUMBER   5 /*每个线程中的小任务*/
#define DELAY_TIME_LEVELS 10.0 /*小任务之间的最大时间间隔*/
int finish_flag =0;

void *thrd_func(void *arg)
{/*线程函数例程*/
    int delay_time = 0;
    int count = 0;

    printf("Thread is starting \n");
    for(count = 0;count< REPEAY_NUMBER;count++)
    {
        delay_time = (int) (rand() * DELAY_TIME_LEVELS/(RAND_MAX))+1;
        sleep(delay_time);
        printf("\t Thread: job %d delay = %d\n",count,delay_time);
    }
    printf("Thread finished \n");
    finish_flag = 1;
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread;
    pthread_attr_t attr;
    int no = 0,res;
    void * thrd_ret;

    srand(time(NULL));
    /*初始化线程属性对象*/
    res = pthread_attr_init(&attr);
    if(res != 0)
    {
        printf("Create attribute failture\n");
        exit(res);
    }
    /*设置线程绑定属性*/
    res = pthread_attr_setscope(&attr,PTHREAD_SCOPE_SYSTEM);
    /*设置线程分离属性*/
    res+= pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    if(res != 0)
    {
        printf("Create attribute failture\n");
        exit(res);
    }
    res = pthread_create(&thread,&attr,thrd_func,NULL);
    if(res != 0)
    {
        printf("Create attribute failture\n");
        exit(res);
    }
    /*释放线程属性对象*/
    pthread_attr_destroy(&attr);
    printf("Create tread success \n");

    while(!finish_flag)
    {
        printf("Waiting for thread to finished ...\n");
        sleep(2);
    }
     return 0;
}

