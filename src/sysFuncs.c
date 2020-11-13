#include "../include/sysFuncs.h"

const char* internal[] = {"cd", "exit"};

int isInternal(char* line){
    for(int i = 0; i < 2; i++){
        if(strcmp(line, internal[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void backgroundProcesses(char** commands){

}

void foregroundProcess(char* commands){
    pid_t pid = fork();
    int status;
    if(pid < 0){
        printf("Não foi possível criar um novo processo\n");
        return;
    }
    char** cmd = formatForeground(commands);
    if(pid == 0){
        execlp(cmd[0], cmd[1], cmd[2], cmd[3]);
    }else{
        waitpid(pid, &status, WUNTRACED);
        freeStringVec(cmd, 4);
    }
}

void internalCommand(char** command){
    if(strcmp(command[0], internal[0]) == 0){
        if(chdir(command[1]) < 0){
            printf("Não foi possível mudar de diretório\n");
        }
    }else if(strcmp(command[0], internal[1]) == 0){
        // codigo de saida da shell
    }
    printf("\n");
}