/*************************************************************************
	> File Name: Guard.c
	> Author: wangmeng 
	> Mail: mwtopfire@gmail.com 
	> Created Time: 2016年10月26日 星期三 10时26分38秒
 ************************************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/syslog.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>

void init_daemon(const char *cmd,int para)
{
    int pid;
    int i;
    signal(SIGTTOU,SIG_IGN);
    signal(SIGTTIN,SIG_IGN);
    signal(SIGTSTP,SIG_IGN);
    signal(SIGHUP,SIG_IGN);
    umask(0);
    if((pid=fork())>0)
    exit(EXIT_SUCCESS);
    else if(pid<0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    setsid();
    if((pid=fork())>0)
    exit(EXIT_SUCCESS);
    else if(pid<0){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    for(i=0;i<NOFILE;++i)
        close(i);
        open("/dev/null",O_RDONLY);
        open("/dev/null",O_RDWR);
        open("/dev/null",O_RDWR);

        chdir("/");
        signal(SIGCHLD,SIG_IGN);
        openlog(cmd,LOG_PID,para); 
        //return;
 }

    int main(int argc,char *argv[]){
        FILE *fp;
        time_t ticks;
        init_daemon(argv[0],LOG_KERN);
        while(1)
        {
            sleep(1);
            ticks=time(NULL);
            syslog(LOG_INFO,"%s",asctime(localtime(&ticks)));
        }
    }

