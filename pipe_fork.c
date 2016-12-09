/*************************************************************************
	> File Name: pipe_fork.c
	> Author: wangmeng 
	> Mail: mwtopfire@gmail.com 
	> Created Time: 2016年11月14日 星期一 22时45分44秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc,char *argv[]){
    int p[2];
    pipe(p);
    char str[10];
   // FILE *fd;
    pid_t pid;
    if((pid=fork())==0){
        close(p[0]);
        int m=getpid();
        sprintf(str,"%d",m);
        write(p[1],str,10);
        close(p[1]);
    }
    else if(pid>0)
    {   sleep(1);
        close(p[1]);
        read(p[0],str,10);
        close(p[0]);
        printf("%s",str);
        system("ps aux");
    }
}
