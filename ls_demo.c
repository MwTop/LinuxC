#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <grp.h>
#include <pwd.h>


 void display_attribute(struct stat buf,char *name){
  char buf_time[32];
  struct passwd *psd;
  struct group *grp;
  if(S_ISLNK(buf.st_mode)){
    printf("l");
  } else if(S_ISREG(buf.st_mode)){
    printf("-");
   } else if(S_ISDIR(buf.st_mode)){
    printf("d");
   } else if(S_ISCHR(buf.st_mode)){
    printf("c");
   } else if(S_ISBLK(buf.st_mode)){
    printf("b");
   } else if(S_ISFIFO(buf.st_mode)){
    printf("f");
   } else if(S_ISSOCK(buf.st_mode)){
    printf("s");
   }
   if(buf.st_mode & S_IRUSR){
     printf("r"); 
   }else {printf("-");}
   if(buf.st_mode & S_IWUSR){
     printf("w"); 
   }else {printf("-");}
   if(buf.st_mode & S_IXUSR){
     printf("x"); 
   }else {printf("-");}
   
   if(buf.st_mode & S_IRGRP){
     printf("r"); 
   }else {printf("-");}
   if(buf.st_mode & S_IWGRP){
     printf("w"); 
   }else {printf("-");}
   if(buf.st_mode & S_IXGRP){
     printf("x"); 
   }else {printf("-");}
   
   
   if(buf.st_mode & S_IROTH){
     printf("r"); 
   }else {printf("-");}
   if(buf.st_mode & S_IWOTH){
     printf("w"); 
   }else {printf("-");}
   if(buf.st_mode & S_IXOTH){
     printf("x"); 
   }else {printf("-");}
   printf("  ");
  
   psd= getpwuid(buf.st_uid);
   grp= getgrgid(buf.st_gid);
   printf("%lu ",buf.st_nlink);
   printf("%8s",psd->pw_name);
   printf("%8s",grp->gr_name);
  
   printf(" %6lu",buf.st_size);
   strcpy(buf_time,ctime(&buf.st_mtime));
   buf_time[strlen(buf_time)-1] ='\0';
   printf("  %s",buf_time);
}
int  main(int argc, char * argv[]){
   DIR  *dir;  
   struct dirent *ptr;
   struct stat  buf;
    if(argc<2)  {
        printf("usage error!\n"); 
        exit(EXIT_FAILURE);  }
   if((dir=opendir(argv[1]))==NULL){
        perror("opendir"); 
         exit(EXIT_FAILURE); 
       }
   
   while((ptr=readdir(dir))!=NULL){
   if(ptr->d_name[0]=='.') 
     continue;

   if(stat(ptr->d_name,&buf)==-1){
     perror("stat:");exit(1); 
   }
   display_attribute(buf,ptr->d_name);
 
     printf(" %s\n",ptr->d_name);
  }
   closedir(dir);
   return 0;
}


