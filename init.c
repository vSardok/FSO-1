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
    int status;
    while(1){ 
        ended = waitpid(-1, &status, 0);
        printf("Ended: %d, Status: %d\n",ended,WEXITSTATUS(status));
        for (int i = 0; i < 6; i++) // Constantemente, revisar todos los hijos
        {
            
            if(ended == procesos[i]){ // Si un hijo finalizo... (se cerro la ventana)
                                      // Verificar si se cerro por un shutdown, en caso de que si, cerrar todos los procesos
                
                if(WEXITSTATUS(status)==4){
                    for (int i = 0; i < 6; i++)
                    {
                        kill(procesos[i], SIGQUIT);
                    }
                    while(wait(NULL)>0);
                    return(0);
                }else{
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
    
}