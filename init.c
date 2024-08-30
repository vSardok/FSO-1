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
        procesos[i]=fork();
        if(procesos[i]==0){
            execlp("xterm", "xterm", "-e", "./getty", NULL);
            //dado caso que no se ejecute para que no continue
            exit(0);
        }
    }
    //codigo para revisar que siempre hayga 6 getty
    while(1){
        ended = wait(NULL);
        for (int i = 0; i < 6; i++)
        {
            if(ended == procesos[i]){
                procesos[i]=fork();
                if(procesos[i]==0){
                    //execlp("sh","sh","xterm -e ./getty",NULL);
                    execlp("xterm", "xterm", "-e", "./getty", NULL);
                    exit(0);
                }
            }
        }
        
    }
    
}