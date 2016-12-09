/*************************************************************************
	> File Name: who.c
	> Author: wangmeng 
	> Mail: mwtopfire@gmail.com 
	> Created Time: 2016年11月21日 星期一 11时11分20秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<wait.h>
  void  main()   {
        int pid,fd;
        printf("This is to show how to redirect!\n");
        if((pid=fork())==-1)      {perror("fork");      exit(1);    }
    else if(pid==0)       {
                  close(1);
                  fd=creat("list.txt",0644);
        if(execlp("ls","ls","-l",NULL)<0)  {
                     perror("exec");
            exit(1);
                       
        }
            
    }
        else if(pid!=0)  {wait(NULL);system("cat list.txt");    }

}
