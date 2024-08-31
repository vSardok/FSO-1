#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#define true 1
#define false 0
pid_t forking;
void sigquit();

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
    //printf("%s\n",con);
    while (fgets(lines,sizeof(lines),file)!=NULL) // Mientras aun haya lineas en el archivo
    {
        //printf("%s\n",lines);
        if(strcmp(lines,con)==0){ // Si un login coincide con el archivo, devuelve true
            printf("Success\n");
            //sleep(1);
            return(true);
        }
    }
    printf("NO USERNAME OR PASSWORD\n"); // Si no se encontro, se notifica al usuario
    fclose(file); // Cerrar el archivo de texto
    return false; // Volver y repetir la funcion
}



int main(){
    signal(SIGQUIT, sigquit);
    pid_t parent = getpid();
    pid_t hijo;
    int status;
    while(1){  // Continuamente
        int promp=false;   // Al inicio de cada ciclo, se vuelve a solicitar el login
        while (promp == false)   
        {
            promp = prompt_login();
        }        
        forking=fork();             // Crear un hijo
        if(forking==0){
            execlp("./sh","sh",NULL);   // El hijo ejecuta sh (./sh)
        }else{  
            hijo = waitpid(-1, &status, 0);               // El padre espera a que acabe el hijo para reiniciar el ciclo
            int statusint=WEXITSTATUS(status);
            // printf("Status %d\n",statusint);
            if(statusint==4){ // Si el hijo acabo con un "shutdown", enviar la señal de salida al padre (init)                       
                //xterm send alwais 0 unless error so im sending a signal to parent
                // sleep(2);
                kill(getppid(),SIGQUIT);
                exit(4);
                // return(0); DIDNT WORK FUCKKKKKK
                // fprintf(stderr, "SHUTDOWN\n");
                // exit(1); didnt work 

                }
                
        }                             
    }
}

void sigquit() {
    if(forking!=0){   // Si un getty tenia un hijo sh activo, tiene que finalizarlo
        kill(forking, SIGKILL); 
    }
    wait(NULL);
    exit(4);
}