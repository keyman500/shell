#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//this function will execute a given file on a new thread.
void execute_file(char * filepath){
 int pid = 0;
 char *args[]={filepath,NULL};
    pid = fork();
    if(pid==0){
        execv(com,args); 
        fflush(stdout);
    }
 
}


int main(void) {
    int pid = 0;
  // printf("PATH : %s\n", getenv("PATH"));
  char *args[]={"./lol",NULL}; 
    char com[50]; 
    printf("[Enter command]>");
    fflush(stdout);
    scanf("%s",com); 

    while(strcmp(com,"exit")){
   // printf("command = %s",com); 
     execute_file(com);
     printf("\n[Enter command]>");
     fflush(stdout);
     scanf("%s",com); 
    }


  
    return 0;
}