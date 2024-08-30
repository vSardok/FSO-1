#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(){
    pid_t procesos[6],ended;
    int i=0;
    for (int i = 0; i < 6; i++)
    {
        procesos[i]=fork(); // Crear los 6 hijos y guardar sus PIDS
        if(procesos[i]==0){
            execlp("xterm", "xterm", "-e", "./getty", NULL); // Reemplazarlos por getty mediante una ventana de xterm (xterm -e ./getty)
            exit(0); //dado caso que no se ejecute para que no continue
        }
    }
    //codigo para revisar que siempre haya 6 getty
    while(1){ 
        ended = wait(NULL);
        for (int i = 0; i < 6; i++) // Constantemente, revisar todos los hijos
        {
            if(ended == procesos[i]){ // Si un hijo finalizo... (se cerro la ventana)
                                      // Verificar si se cerro por un shutdown, en caso de que si, cerrar todos los procesos
                procesos[i]=fork(); // Crear uno nuevo y guardar su pid
                if(procesos[i]==0){
                    //execlp("sh","sh","xterm -e ./getty",NULL);
                    execlp("xterm", "xterm", "-e", "./getty", NULL); // Reemplazarlo por la ventana de xterm (xterm -e ./getty)
                    exit(0); //dado caso que no se ejecute para que no continue
                }
            }
        }
        
    }
    
}