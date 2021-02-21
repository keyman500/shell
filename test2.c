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

char *test(){
    char s[200] = "lol";
    return s;
}

int main(void)

{
    char *s = test();
    printf("%s",s);
  

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