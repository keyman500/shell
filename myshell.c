
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#define maxchar 50


//returns 1 if file exists in current directory and 0 if it does not
int file_exists(char *path){
struct stat stats;
if (stat(path, &stats) == 0){
    return 1;
}
return 0;
}

char *sea(char *command[],char *paths[],int i){
    char path[200] = "/";
    char *temp = (char*) malloc((201)*sizeof(char));
    temp = "";
    int k = 0;
    strcat(path, command[0]);
    for(k=0;k<i;k++){
              strcpy(temp,paths[k]);
              strcat(temp,path);
        if(file_exists(temp)){
         return temp;
        }
   }
   return "failed too find file";
}

void prep_pipe(char **args,char *s1[],char *s2[], char **paths, int o){
int i =0;
while(args[i]!=NULL){
strcpy(s1[i], args[i]);
i++;
}
s1[i]= NULL;
i++;
int k =0;
while(args[i]!=NULL){
    strcpy(s2[k], args[i]);
    i++;
    k++;
}
s2[k] = NULL;
char b1[20] ="/bin/";
char b2[20] ="/bin/";
strcat(b1,s1[0]);
strcat(b2,s2[0]);
//s2[0]=b2;
//s1[0]=b1;

}


void run_pipe(char *args1[],char *args2[]){
    int p1,p2;
    int fd[2];
    pipe(fd);
    printf("\ntets|%s|\n",args2[0]);
    p1 = fork();
    if(p1==0){
    dup2(fd[1],1);
    close(fd[0]);
    close(fd[1]);
    execv(args1[0],args1); 
    }
   p2 = fork();
    if(p2==0){
        dup2(fd[0],0);
        close(fd[0]);
        close(fd[1]);
        printf("in fin: |%s|",args2[0]);
        execv(args2[0],args2);
        //execlp("grep","grep","main",NULL);
    }

    close(fd[0]);
    close(fd[1]);
    waitpid(p1,NULL,0);
    waitpid(p2,NULL,0);

}

//this function takes the user input as command and seperates it by spaces putting each word in the array
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

//this function checks if a string contains a character and returns the postion of the character or -1 if the character is not there.
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
int pid2;
  int fd1;
 int r = check_char(args,">");
 int p = check_char(args,"|");

if(p>-1){
char * s1[10] ={"/bin/ls",NULL};
char * s2[10] = {};
args[p]= NULL;
prep_pipe(args,s1,s2,paths,i);
printf("%s",s2[0]);
run_pipe(s1,s2);
}
else{
 int pid = 0;
    pid = fork();
    
    if(pid==0){

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
      
     sleep(1);
}
}


//this function searches for the command or file in the path and executes the file.
void search(char *command[],char *paths[],int i){
    char path[200] = "/";
    char temp[200]="";
    
    int k = 0;
    strcat(path, command[0]);
    for(k=0;k<i;k++){
              strcpy(temp,paths[k]);
              strcat(temp,path);
        if(file_exists(temp)){
       execute_file(temp,command,paths,i);
         break;
        }
   }
}


// this function gets the path varible puts it into an array it returns the size of the array
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
     execute_file(list[0],list,paths,h);
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