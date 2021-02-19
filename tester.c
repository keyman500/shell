#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
int search(char **paths){
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
int file_exists(char *path){
struct stat stats;
if (stat(path, &stats) == 0){
    return 1;
}
return 0;
}


int main( void )

{
    int i =0;
    char *paths[50]= {};
    i= search(&paths);
    for(int k=0;k<i;k++){
       printf("\n%s",paths[k]);
   }

  return 0;

}