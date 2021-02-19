#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#define maxchar 50
int fill_array(char command[],char*arr[]){
	int i =0;
    char delim[] = " ";
	char *ptr = strtok(command, delim);
	while(ptr != NULL)
	{
        arr[i] = ptr;
		ptr = strtok(NULL, delim);
        i++;
	}
    arr[i] = NULL;
    return i;
}
//this function will execute a given file(program) on a new thread.
void execute_file(char *path,char *args[]){
 int pid = 0;
    pid = fork();
    if(pid==0){
        execv(path,args); 
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

void search(char *command[],char *paths[],int i){
    char path[200] = "/";
    char temp[200]="/bin";
    int k = 0;
    strcat(path, command[0]);
    for(k=0;k<i;k++){
              strcpy(temp,paths[k]);
              strcat(temp,path);
        if(file_exists(temp)){
       execute_file(temp,command);
         break;
        }
   }
}

int get_paths(char *paths[]){
    int i =0;
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
    char *paths[50];
    char com[maxchar]; 
    char *list[10]={};
    int i = 0;
    printf("[Enter command]>");
    fflush(stdout);
    fgets(com,maxchar, stdin);  
    com[strcspn(com, "\n")] = 0;
    
    //filling array with seperated words.
    fill_array(com,list);

    int h = get_paths(paths);

    
    while(strcmp(com,"exit")){
     if(file_exists(list[0]))
     execute_file(list[0],list);
     else{
     search(list,paths,h);
     }
     printf("\n[Enter command]>");
     fflush(stdout);
     fgets(com,maxchar, stdin); 

     com[strcspn(com, "\n")] = 0;
    
        
    //filling array
    fill_array(com,list);
    //end filling array
    }
    return 0;

}