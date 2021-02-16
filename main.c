#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define maxchar 50
//this function will execute a given file on a new thread.
void execute_file(char *args[]){
 int pid = 0;
    pid = fork();
    if(pid==0){
        execv(args[0],args); 
        fflush(stdout);
    }
 
}
//returns 1 if file exists in current directory and 0 if it does not
int file_exists(char *path){
struct stat stats;
printf("%smk",path);
if (stat(path, &stats) == 0){
    return 1;
}
return 0;
}

char *strip(char * str){
    int i=0;
while(str[i]!=NULL){
i++;
}
str[i-1] = NULL;
return str;
}

int main(void) {
    int pid = 0;
  // printf("PATH : %s\n", getenv("PATH"));

    char com[maxchar]; 
    char *list[10]={};
    int i = 0;
    printf("[Enter command]>");
    fflush(stdout);
    fgets(com,maxchar, stdin);  
    //filling array
	char delim[] = " ";
	char *ptr = strtok(com, delim);
	while(ptr != NULL)
	{
		printf("'%s'\n", ptr);
        list[i] = ptr;
		ptr = strtok(NULL, delim);
        i++;
	}
    list[i] = NULL;



    while(strcmp(com,"exit")){
   // printf("command = %s",com);
     if(file_exists(list[0])) 
     execute_file(list);
     else
     printf("file not found!");
     printf("\n[Enter command]>");
     fflush(stdout);
     scanf("%s",com); 
    }


  
    return 0;
}