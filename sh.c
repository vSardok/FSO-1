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
        if(strcmp(str,exitcmp)==0){ // Si el usuario quiere salir, cerrar el proceso sh
            //regresar
            exit(0);
        }else if(strcmp(str,shudown)==0){ // todo: Si el usuario quiere salir, cerrar todos los procesos 
            //parar todo
            exit(4);
        }else{
            pid_t eje;
            eje=fork();  // Crear un hijo
            if(eje==0){
                execlp(str,str,NULL); // El hijo ejecutara el comando
            }else{
                wait(NULL);     // Esperar a que acabe el hijo
            }
        }
    }
    exit(0);
}