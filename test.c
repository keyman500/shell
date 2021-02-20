#include <stdio.h>
#include <string.h>
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

int main(void)

{
    char *args[10] ={"ls","fam","llll","bat.txt"};
    int x =check_redirect(args);
    printf("%d",x);


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