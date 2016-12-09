#include <stdio.h>
#include <stdlib.h>
#include <utime.h>
#include <string.h>
#include <pwd.h>
#include <dirent.h>
#include <sys/stat.h>
#define NAME_SIZE 256
struct fnode{
  struct fnode *next;
  char name[NAME_SIZE];
};
struct group{
  char *gr_name;
  char *gr_passwd;
 // _gid_t gr_gid;  //group GID
    char **gr_mem;
};
 //output_type_perm(mode_t mode);
 void output_user_group(uid_t uid,gid_t gid);
// output_mtime(time_t mytime);
 void output_info(struct fnode *head);

int main(int argc,char *argv[]){
   if(argc < 2)
   {
      printf("usage :%s dir_name\n",argv[0]);
      exit(EXIT_FAILURE);
   }

   int i;
   for(i=1;i<argc;i++){
      struct fnode *linklist = NULL;
      struct stat stat_info;
      if(stat(argv[i],&stat_info)==-1)
      {perror("stat");
      exit(EXIT_FAILURE);
      }
      if(S_ISREG(stat_info.st_mode))
      {
         struct fnode *temp = (struct fnode *)malloc(sizeof(struct fnode));
         if(NULL==temp){
           perror("malloc");
           exit(EXIT_FAILURE);
         }
         temp->next=NULL;
         memset(temp->name,'\0',NAME_SIZE);
         memcpy(temp->name,argv[i],strlen(argv[i]));
         linklist = insert_list(temp,linklist);
         output_info(linklist);
      }
      else if(S_ISDIR(stat_info.st_mode)){
        char buf[NAME_SIZE];
        getcwd(buf,128);
        DIR *dirp=NULL;
        dirp=opendir(argv[i]);
        if(NULL==dirp){
           perror("opendir");
           exit(EXIT_FAILURE);
        }
        struct dirent *entp=NULL;
        while(entp=readdir(dirp))
        {
           struct fnode *temp=(struct fnode *)malloc(sizeof(struct fnode));
           if(NULL==temp){
              perror("malloc");
             exit(EXIT_FAILURE);
           }
         temp->next=NULL;
         memset(temp->name,'\0',NAME_SIZE);
         memcpy(temp->name,entp->d_name,strlen(entp->d_name));
         linklist = insert_list(temp,linklist);
        }
        chdir(argv[i]);
        close(dirp);
        output_info(linklist);
        chdir(buf);
      }
      free_list(linklist);
   }
   return 1;
}

 void output_type_perm(mode_t mode){
   char type[7]={'p','c','d','b','-','l','s'};
     int index = ((mode >>12)& 0xF)/2;
     printf("%c",type[index]);

     char *perm[8]={"---","--x","-w-","-wx","r--","r-x","rw-","rwx"};
    printf("%s",perm[mode>>6 &07]);
    printf("%s",perm[mode>>3 &07]);
     printf("%s",perm[mode>>0 &07]);
 }

 void output_user_group(uid_t uid,gid_t gid)
 {
    struct passwd *user;
     user=getpwuid(uid);
     printf("   %s",user->pw_name);

     struct group *group;
     group=getgrgid(gid);
     printf("%s",group->gr_name);
 }
  
void output_mtime(time_t mytime)
{
   char buf[256];
    memset(buf,'\0',256);
    ctime_r(&mytime,buf);
    buf[strlen(buf)-1]='\0';
    printf("  %s",buf);
}

void output_info(struct fnode *head)
{
    struct fnode *temp=head;
    while(temp!=NULL){
       struct stat mystat;
        if(-1==stat(temp->name,&mystat))
        {
           perror("stat");
           exit( EXIT_FAILURE);
        }
        output_type_perm(mystat.st_mode);
        printf("%d",mystat.st_nlink);
        output_user_group(mystat.st_uid,mystat.st_gid);
        printf(" %8ld",mystat.st_size);
        output_mtime(mystat.st_mtime);
        printf("  %s\n",temp->name);
        temp=temp->next;
    }
}
