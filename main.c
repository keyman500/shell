#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#define true 1
#define false 0
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

int check_char(char *args[],char *s){
    int i =0;
    while(args[i]!=NULL){
        if(!strcmp(args[i],s)){
          return i;
        }
        i++;
    }
return -1;
}
//this function will execute a given file(program) on a new thread.

void execute_file(char *path,char *args[],char *paths[],int i){
  int fd1;
 int r = check_char(args,">");
 int p = check_char(args,"|");
int fd[2];
pipe(fd);



 int pid = 0;
    pid = fork();
    
    if(pid==0){
//handling pipe
if(p>-1){
dup2(fd[1],1);
close(fd[0]);
close(fd[1]);
args[p] = NULL;
}
//end handling pipe

//handling redirect 
  if(r> -1&&p==-1){
  fd1 = creat(args[r+1], 0644);
  dup2(fd1, 1);
  close(fd1);
  args[r]=NULL;
 }
 //end handling redirect 
 
        execv(path,args); 
        fflush(stdout);
    }

    //child 2
    if(p>-1){
        char *path2 = search2(args[p+1],paths,i);
        int pid2 =fork();
        if(pid2==0){
        dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);
        execv(path,args); 
        fflush(stdout);
        }
    }
    //end child 2



close(fd[0]);
close(fd[1]);
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
    char temp[200]="";
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
char * search2(char *command[],char *paths[],int i){
    char path[200] = "/";
    char temp[200]="";
    int k = 0;
    strcat(path, command[0]);
    for(k=0;k<i;k++){
              strcpy(temp,paths[k]);
              strcat(temp,path);
        if(file_exists(temp)){
         return temp;
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