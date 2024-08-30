#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#define true 1
#define false 0

int prompt_login() {
    FILE *file;
    char login[100], password[100],lines[100],con[2001];
    char*dots=":";
    printf("login: ");
    scanf("%s", login);
    printf("password: ");
    scanf("%s", password);
    file = fopen("psswd.txt","r"); // Abrir el archivo de texto
    strcpy(con,login);
    strcat(con,dots);
    strcat(con,password); // Construir el login
    printf("%s\n",con);
    while (fgets(lines,sizeof(lines),file)!=NULL) // Mientras aun haya lineas en el archivo
    {
        printf("%s\n",lines);
        if(strcmp(lines,con)==0){ // Si un login coincide con el archivo, devuelve true
            printf("Success\n");
            sleep(1);
            return(true);
        }
    }
    printf("NO USERNAME OR PASSWORD\n"); // Si no se encontro, se notifica al usuario
    fclose(file); // Cerrar el archivo de texto
    return false; // Volver y repetir la funcion
}



void main(){
    while(1){  // Continuamente
        int promp=false;   // Al inicio de cada ciclo, se vuelve a solicitar el login
        while (promp == false)   
        {
            promp = prompt_login();
        }
        pid_t sh;              // Tras login exitoso
        sh=fork();             // Crear un hijo
        if(sh==0){
            execlp("./sh","sh",NULL);   // El hijo ejecuta sh (./sh)
        }else{
            wait(NULL);                 // El padre espera a que acabe el hijo para reiniciar el ciclo
                                        // Si el hijo acabo con un "shutdown", enviar la señal de salida al padre (init)
        }                             
    }
    exit(0);
}