/*thread-sem.c*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

#define THREAD_NUMBER   3 /*线程数*/
#define REPEAY_NUMBER   5 /*每个线程中的小任务*/
#define DELAY_TIME_LEVELS 10.0 /*小任务之间的最大时间间隔*/
sem_t sem[THREAD_NUMBER];

void *thrd_func(void *arg)
{/*线程函数例程*/
    int thrd_num = (int)arg;
    int delay_time = 0;
    int count = 0;

    /**进行P操作*/
    sem_wait(&sem[thrd_num]);
    printf("Thread %d is starting \n",thrd_num);

    for(count = 0;count< REPEAY_NUMBER;count++)
    {
        delay_time = (int) (rand() * DELAY_TIME_LEVELS/(RAND_MAX))+1;
        sleep(delay_time);
        printf("\t Thread %d: job %d delay = %d\n",thrd_num,count,delay_time);
    }
    printf("Thread %d finished \n",thrd_num);
    pthread_exit(NULL);
}

int main(void)
{
    pthread_t thread[THREAD_NUMBER];
    int no = 0,res;
    void * thrd_ret;

    srand(time(NULL));

    for(no =0;no < THREAD_NUMBER; no ++)
    {
        sem_init(&sem[no],0,0);
        /*创建多线程*/
        res = pthread_create(&thread[no],NULL,thrd_func,(void*)no);
        if(res != 0)
        {
            printf("Create thread %d failed \n",no);
            exit(res);
        }
    }

    printf("Create tread success\n Waiting for threads to finish...\n");
    /*对最后创建的线程的信号量进行V操作*/
    sem_post(&sem[THREAD_NUMBER - 1]);
    for(no=THREAD_NUMBER-1;no>=0;no--)
    {
        /*等待线程结束*/
        res = pthread_join(thread[no],&thrd_ret);
        if(!res)
        {
            printf("Thread %d jioned \n",no);
        }
        else
        {
            printf("Thread %d jion failed \n",no);
        }
        /*进行V操作*/
        sem_post(&sem[(no+THREAD_NUMBER-1)%THREAD_NUMBER]);
    }

    for(no = 0;no<THREAD_NUMBER;no++)
    {
        /*删除信号量*/
        sem_destroy(&sem[no]);
    }
     return 0;
}
