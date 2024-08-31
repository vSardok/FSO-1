#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
    char str[100];
    char *cmdargs[16];
    while(1){
        printf("sh> ");
        //scanf("%s",str); // Scanf corta el string en cuanto recibe un espacio
        fgets(str, 100, stdin);
        str[strcspn(str,"\n\r")] = 0;
        //printf("Ejecutando %s.\n", str); // Debug del string
        cmdargs[0] = strtok(str," ");  // Identificar el comando a ejecutar
        if(strcmp(cmdargs[0],"exit")==0){ // Si el usuario quiere salir, cerrar el proceso sh
            //regresar
            exit(0);
        }else if(strcmp(cmdargs[0],"shutdown")==0){ // Si el usuario quiere salir, cerrar todos los procesos 
            //parar todo
            exit(4);
        }else{
            pid_t eje;
            eje=fork();  // Crear un hijo
            if(eje==0){
                int i=0;
                while(cmdargs[i]!=NULL) // Agregar los parametros 
                {
                    i++;
                    cmdargs[i] = strtok(NULL," ");
                }
                //for (int j=0; j<=i; j++) printf("%s ",cmdargs[j]); // Debbug de los argumentos
                execvp(cmdargs[0],cmdargs); // El hijo ejecutara el comando
                exit(0); // Si el comando es incorrecto, el hijo debe acabar para no duplicar los procesos
            }else{
                wait(NULL);     // Esperar a que acabe el hijo
            }
        }
    }
    exit(0);
}