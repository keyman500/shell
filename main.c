#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
//this function will execute a given file on a new thread.
void execute_file(char * filepath){
 int pid = 0;
 char *args[]={filepath,NULL};
    pid = fork();
    if(pid==0){
        execv(args[0],args); 
        fflush(stdout);
    }
 
}
//returns 1 if file exists in current directory and 0 if it does not
int file_exists(char *path){
struct stat stats;
if (stat(path, &stats) == 0){
    return 1;
}
return 0;
}

int main(void) {
    int pid = 0;
  // printf("PATH : %s\n", getenv("PATH"));

    char com[50]; 
    printf("[Enter command]>");
    fflush(stdout);
    scanf("%s",com); 

    while(strcmp(com,"exit")){
   // printf("command = %s",com);
     if(file_exists(com)) 
     execute_file(com);
     else
     printf("file not found!");
     printf("\n[Enter command]>");
     fflush(stdout);
     scanf("%s",com); 
    }


  
    return 0;
}