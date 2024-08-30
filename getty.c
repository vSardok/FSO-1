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
    file = fopen("init.txt","r");
    strcpy(con,login);
    strcat(con,dots);
    strcat(con,password);
    printf("%s\n",con);
    while (fgets(lines,sizeof(lines),file)!=NULL)
    {
        printf("%s\n",lines);
        if(strcmp(lines,con)==0){
            printf("Success\n");
            sleep(1);
            return(true);
        }
    }
    printf("NO USERNAME OR PASSWORD\n");
    fclose(file);
    
    return false;
}



void main(){
    while(1){
        int promp=false;
        while (promp == false)
        {
            promp = prompt_login();
        }
        pid_t sh;
        sh=fork();
        if(sh==0){
            execlp("./sh","sh",NULL);
        }else{
            wait(NULL);
        }
    }
    exit(0);
}