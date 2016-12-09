/*************************************************************************
	> File Name: signal_uid.c
	> Author: wangmeng 
	> Mail: mwtopfire@gmail.com 
	> Created Time: 2016年11月21日 星期一 12时58分47秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

void UID() { 

     printf("SIGINT is captured!\n");
     printf("this process uid:%d\n",getuid());
    signal(SIGINT,SIG_DFL);
}

void pid(){
    printf("SIGTERM is captured!\n");
    printf("the pid is %d\n",getpid());
    signal(SIGINT,SIG_DFL);
}

int main( )  {
         int i=10; 
        // signal(SIGINT,UID); 
         signal(SIGINT,pid); 
         printf("waiting for signal...\n"); 
    while(i>0)    {
            sleep(1);
             i--;   
            
    }
    return 0;
}

