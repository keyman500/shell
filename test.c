#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
int check_redirect(char *args[]){
    int i =0;
    while(args[i]!=NULL){
        if(!strcmp(args[i],">")){
          return i;
        }
        i++;
    }
return -1;
}

void run_pipe(char *args1,char *args2){
    int pid1,pid2;
    int fd[2];
    pipe(fd);
    pid1 = fork();
    if(pid1==0){
    dup2(fd[1],1);
    close(fd[0]);
    close(fd[1]);
    execv(args1[0],args1); 
    }
   pid2 = fork();
    if(pid2==0){
        dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);
        execv(args2[0],args2);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);

}

int main(void)

{
    char *args1[20]={"/bin/ls",NULL};
    char *args2[20]= {"/bin/grep","main",NULL};
    int pid1,pid2;
    int fd[2];
    pipe(fd);
    pid1 = fork();
    if(pid1==0){
    dup2(fd[1],1);
    close(fd[0]);
    close(fd[1]);
    execv(args1[0],args1); 
    }
   pid2 = fork();
    if(pid2==0){
        dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);
        execv(args2[0],args2);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(pid1,NULL,0);
    waitpid(pid2,NULL,0);


  return 0;

}




    /*
    function too determine how much values in array
int i=0;
char *arr[10] = {"ok","ok",NULL};
int x = sizeof(arr) / sizeof(char**);
for(i=0;i<x;i++){
    if(arr[i]==NULL){
        break;
    }
}
printf("%d",i);
*/