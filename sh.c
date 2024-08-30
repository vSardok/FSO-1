#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
    char str[100];
    char *exitcmp="exit";
    char *shudown ="shutdown";
    while(1){
        printf("sh> ");
        scanf("%s",str);
        if(strcmp(str,exitcmp)==0){
            //regresar
        }else if(strcmp(str,shudown)==0){
            //parar todo
            exit(0);
        }else{
            pid_t eje;
            eje=fork();
            if(eje==0){
                execlp(str,str,NULL);
            }else{
                wait(NULL);
            }
        }
    }
    exit(0);
}