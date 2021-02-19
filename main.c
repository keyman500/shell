#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define maxchar 50
//this function will execute a given file(program) on a new thread.
void execute_file(char *args[]){
 int pid = 0;
    pid = fork();
    if(pid==0){
        execv(args[0],args); 
        fflush(stdout);
    }
      //sleep is called too allow the output from the new thread too be printed before the user is promted again.
     sleep(1);
}
//returns 1 if file exists in current directory and 0 if it does not
int file_exists(char *path){
struct stat stats;
if (stat(path, &stats) == 0){
    return 1;
}
return 0;
}
int search(char *command){
    char *path = "/";
    strcat(path, command);
    char **paths;
    int i =0;
    i= get_paths(&paths);
    
    for(int k=0;k<i;k++){
        	strcat(path[k],path);
        if(file_exists(paths[k])){
        printf("found bin at: %s",paths[k]);
        }
      
   }
   return 0;

}

int get_paths(char **paths){
    int i =0;
   // char *paths[50]={};
    char *path = getenv("PATH");
    char delim[] = ":";
	char *ptr = strtok(path, delim);
	while(ptr != NULL)
	{
        paths[i] = ptr;
		ptr = strtok(NULL, delim);
        i++;
	}

  return i;

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
    com[strcspn(com, "\n")] = 0;
    
    //filling array
	char delim[] = " ";
	char *ptr = strtok(com, delim);
	while(ptr != NULL)
	{
        list[i] = ptr;
		ptr = strtok(NULL, delim);
        i++;
	}
    list[i] = NULL;
    //end filling array


    while(strcmp(com,"exit")){
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