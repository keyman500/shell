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

    char *s = (char*) malloc((100+1)*sizeof(char));
    s = "lol";
    return s;
}

void prep_pipe(char **args,char *s1[],char *s2[]){
int i =0;
while(args[i]!=NULL){
s1[i]= args[i];
i++;
}
s1[i]= NULL;
i++;
int k =0;
while(args[i]!=NULL){
    s2[k] = args[i];
    i++;
    k++;
}
s2[k] = NULL;

}
int main(void)

{
char *s1[20]={};
char *s2[20]={};
char *args[20]={"ls",NULL,"grep","main",NULL};
prep_pipe(args,s1,s2);
printf("%s",s2[1]);

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