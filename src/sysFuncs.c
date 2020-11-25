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
    int pidM = fork();
    if(pidM == 0){
        setsid();
        int pids[5] = {-1, -1, -1, -1, -1};
        for(int i = 0; i < 5 && commands[i] != NULL; i++){
            char** cmd = formatCmd(commands[i]);
            pids[i] = fork();
            if(pids[i] == 0){
                if(execlp(cmd[0], cmd[0] ,cmd[1], cmd[2], cmd[3], NULL) < 0){
                    perror("Não foi possivel rodar o programa");
                }
                exit(1);
            }else if(pids[i] > 0){
                freeStringVec(cmd, 4);
            }
        }
        int status;
        while(waitpid(-1, &status, WNOHANG) > 0){
            if(WIFSIGNALED(status)){
                if(WTERMSIG(status) == SIGUSR1){
                    killpg(0, SIGUSR1);
                }
            }
        }
        exit(0);
    }
}

void foregroundProcess(char* commands){
    pid_t pid = fork();
    if(pid < 0){
        perror("Não foi possível criar um novo processo");
        return;
    }
    char** cmd = formatCmd(commands);
    if(pid == 0){
        if(execlp(cmd[0], cmd[0] ,cmd[1], cmd[2], cmd[3], NULL) < 0){
            perror("Não foi possivel rodar o programa");
        }
        exit(1);
    }else{
        setHandler(SIG_IGN);
        waitpid(pid, NULL, 0);
        setHandler(handleSignal);
        freeStringVec(cmd, 4);
    }
}
void internalCommand(char** command){
    if(strcmp(command[0], internal[0]) == 0){
        if(chdir(command[1]) < 0){
            perror("Não foi possível mudar de diretório");
        }
    }else if(strcmp(command[0], internal[1]) == 0){
        // codigo de saida da shell
    }
}