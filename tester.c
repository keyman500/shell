#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
int search(char command[]){
    char path[200] = "/";
    strcat(path, command);
    char *paths[600];
    int i =0;
    i= get_paths(&paths);
    
    for(int k=0;k<i;k++){
      	strcat(paths[k],path);
        if(file_exists(paths[k])){
        printf("\nfound bin at: %s",paths[k]);
        }
      
   }
   return 0;

}
int file_exists(char *path){
struct stat stats;
if (stat(path, &stats) == 0){
    return 1;
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

int main( void )

{
    char * s= "ls";
int x = search(s);

  return 0;

}