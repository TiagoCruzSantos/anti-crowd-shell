#include "../include/sysFuncs.h"

int acshExit;

void acshExited(int i){
    acshExit = 1;
}

const char* internal[] = {"cd", "exit"};

int isInternal(char* line){
    for(int i = 0; i < 2; i++){
        if(strcmp(line, internal[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void backgroundProcesses(char** commands, TipoLista* procs){
    int pidM = fork();

    if(pidM == 0){
        LiberaLista(procs);
        acshExit = 0;
        setsid();
        struct sigaction chlTerm;
        chlTerm.sa_handler = SIG_DFL;
        chlTerm.sa_flags = SA_RESETHAND;
        sigemptyset(&chlTerm.sa_mask);
        sigaction(SIGCHLD, &chlTerm, NULL);
        int pids[5] = {-1, -1, -1, -1, -1};
        for(int i = 0; i < 5 && commands[i] != NULL; i++){
            char** cmd = formatCmd(commands[i]);
            pids[i] = fork();
            if(pids[i] == 0){
                if(commands[1] == NULL){
                    struct sigaction sigusrIgn;
                    sigusrIgn.sa_handler = SIG_IGN;
                    sigemptyset(&sigusrIgn.sa_mask);
                    sigaction(SIGUSR1, &sigusrIgn, NULL);
                }
                if(execlp(cmd[0], cmd[0] ,cmd[1], cmd[2], cmd[3], NULL) < 0){
                    perror("Não foi possivel rodar o programa");
                }
                exit(1);
            }else if(pids[i] > 0){
            }else{
                perror("Não foi possível criar novo processo");
            }
        }
        struct sigaction acshTerm;
        acshTerm.sa_handler = acshExited;
        sigemptyset(&acshTerm.sa_mask);
        sigaction(SIGUSR2, &acshTerm, NULL);
        int status;
        int sigAct = 0;
        int pid;
        while((pid = waitpid(-1, &status, WNOHANG)) != -1){
            if(acshExit){
                break;
            }
            if(pid > 0 && WIFSIGNALED(status)){
                if(WTERMSIG(status) == SIGUSR1){
                    sigAct = 1;
                    break;
                }
            }
        }
        if(acshExit){
            for(int i = 0; i < 5 && pids[i] != -1; i++){
                kill(pids[i], SIGTERM);
            }
        }
        if(sigAct){
            for(int i = 0; i < 5 && pids[i] != -1; i++){
                kill(pids[i], SIGUSR1);
            }
        }
        exit(0);
    }else if(pidM > 0){
        Insere(pidM, procs);
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
        struct sigaction chlTerm;
        chlTerm.sa_handler = SIG_DFL;
        sigemptyset(&chlTerm.sa_mask);
        sigaction(SIGCHLD, &chlTerm, NULL);
        waitpid(pid, NULL, 0);
        chlTerm.sa_handler = chldTerm;
        sigaction(SIGCHLD, &chlTerm, NULL);
        setHandler(handleSignal);
        freeStringVec(cmd, 4);
    }
}
void internalCommand(char** command, TipoLista* listaDeProcessos){
    if(strcmp(command[0], internal[0]) == 0){
        if(chdir(command[1]) < 0){
            perror("Não foi possível mudar de diretório");
        }
    }else if(strcmp(command[0], internal[1]) == 0){
        while(!Vazia(listaDeProcessos)){
            kill(RetiraPrimeiro(listaDeProcessos), SIGUSR2);
        }
        exit(0);
    }
}