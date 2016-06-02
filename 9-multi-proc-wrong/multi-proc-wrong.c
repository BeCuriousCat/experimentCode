/*mulit_proc_wrong.c*/
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void){
	pid_t child1,child2,child;
	/*创建两个子进程*/
	child1 = fork();	
	child2 = fork();
        
	printf("child1 = %d, child2 =%d,pid=%d,ppid = %d  \n",child1,child2,getpid(),getppid());
	/*子进程1的出错处理*/
        if(child1 == -1){              
                printf("Child1 fork error\n");
                exit(1);
        }
        else if( child1 == 0 )/* 在子进程中调用execlp()函数*/
        {
                printf("In Child1: execute 'ls -l' the pid =%d \n",getpid());
                if(execlp("ls","ls","-l",NULL)<0)
                {
                        printf("Child1 execlp error \n");
                }
        }
	/*子进程2的出错处理*/
        if(child2 == -1)
        {
                printf("child2 fork error \n");
                exit(1);
        }
        else if( child2 == 0 )
        {
                printf("In Child2: sleep for 5 seconds and then exit \n");
                sleep(5);
                exit(0);
        }
        else /* 在父进程中等待两个子进程的退出*/
        {
                printf("In father process: \n");
                child = waitpid(child1,NULL,0);/*阻塞式等待*/
                if(child == child1)		/*若waitpaid返回值为child1的pid则 child1退出 */
                {
                        printf("Get child1 exit code \n");
                }
                else
                {
                        printf("Error occured!\n");
                }
                do
                {
                        child = waitpid(child2,NULL,WNOHANG);/*非阻塞式等待*/
                        if( child == 0 )	/*若输出的返回值为0 ，则说明 child2 这个子进程还没有结束*/
                        {	
                                printf("The child2 process has not exited !\n");
                                sleep(1);
                        }
                }while(child == 0);		/*当子进程还没有结束的时候就让它一直循环判断*/

                if( child  == child2 ){		/*如果返回值是child2的进程号，就打印子进程2已经结束*/
                        printf("Get child2 exit code \n");
                }else
                {
                        printf("Error occured!\n"); /*否则则报错。*/
                }
        }
        exit(0);
}
