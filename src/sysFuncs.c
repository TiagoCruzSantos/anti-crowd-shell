#include "../include/sysFuncs.h"

int acshExit;

/* Chamado quando o processo principal envia SIGUSR2 */
void acshExited(int i){
    if(i == SIGUSR2){
        acshExit = 1;
    }
}

const char* internal[] = {"cd", "exit"};// Comandos internos

int isInternal(char* line){
    for(int i = 0; i < 2; i++){ // Verifica se existe o comando nos comandos internos
        if(strcmp(line, internal[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void backgroundProcesses(char** commands, TipoLista* procs){
    int pidM = fork(); // Cria novo processo intermediario

    if(pidM == 0){
        LiberaLista(procs);
        acshExit = 0;
        setsid();
        struct sigaction chlTerm; // Retira o tratador de SIGCHLD
        chlTerm.sa_handler = SIG_DFL;
        chlTerm.sa_flags = SA_RESETHAND;
        sigemptyset(&chlTerm.sa_mask);
        sigaction(SIGCHLD, &chlTerm, NULL);
        int pids[5] = {-1, -1, -1, -1, -1};// Lista dos processos irmãos
        for(int i = 0; i < 5 && commands[i] != NULL; i++){
            char** cmd = formatCmd(commands[i]);
            pids[i] = fork();
            if(pids[i] == 0){
                if(commands[1] == NULL){ // Ignora SIGUSR1 caso seja o único processo
                    struct sigaction sigusrIgn = {.sa_handler = SIG_IGN};
                    sigemptyset(&sigusrIgn.sa_mask);
                    sigaction(SIGUSR1, &sigusrIgn, NULL);
                }
                if(execlp(cmd[0], cmd[0] ,cmd[1], cmd[2], cmd[3], NULL) < 0){
                    perror("Não foi possivel rodar o programa");
                }
                exit(1);
            }else if(pids[i] > 0){
                freeStringVec(cmd, 4);
            }else{
                perror("Não foi possível criar novo processo");
            }
        }
        freeStringVec(commands, 5);
        struct sigaction acshTerm = {.sa_handler = acshExited}; // Adiciona tartador para o sinal SIGUSR2 que sera enviado pelo acsh após um exit
        sigemptyset(&acshTerm.sa_mask);
        sigaction(SIGUSR2, &acshTerm, NULL);
        int status;
        int sigAct = 0;
        int pid;
        while((pid = waitpid(-1, &status, WNOHANG)) != -1){ // Espera por todos os filhos
            if(acshExit){ // Caso o acsh tenha executado exit
                break;
            }
            if(pid > 0 && WIFSIGNALED(status)){
                if(WTERMSIG(status) == SIGUSR1){ // Caso um processo tenha saido com sinal SIGUSR1
                    sigAct = 1;
                    break;
                }
            }
        }
        if(acshExit){ // Mata todos os filhos caso acsh tenha dado exit
            for(int i = 0; i < 5 && pids[i] != -1; i++){
                kill(pids[i], SIGTERM);
            }
        }
        if(sigAct){// Mata todos os processos caso um dos filhos tenha dado SIGUSR1
            for(int i = 0; i < 5 && pids[i] != -1; i++){
                kill(pids[i], SIGUSR1);
            }
        }
        exit(0);
    }else if(pidM > 0){
        Insere(pidM, procs);// Adiciona novo processo intermediario a lista de processos
        freeStringVec(commands, 5);
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
        setHandler(SIG_IGN); // Ignora os sinais SIGINT, SIGQUIT e SIGTSTP enquanto o processo em foreground estiver ativo
        struct sigaction chlTerm = {.sa_handler = SIG_DFL}; // Retira tratador do SIGCHLD
        sigemptyset(&chlTerm.sa_mask);
        sigaction(SIGCHLD, &chlTerm, NULL);
        waitpid(pid, NULL, 0);
        setHandler(handleSignal); // Retorna com a mensagem a ser printada caso SIGINT, SIGQUIT e SIGTSTP
        chlTerm.sa_handler = chldTerm; // Retorna com tratador do SIGCHLD
        sigaction(SIGCHLD, &chlTerm, NULL);
        freeStringVec(cmd, 4);
    }
}
void internalCommand(char** command, TipoLista* listaDeProcessos){
    if(strcmp(command[0], internal[0]) == 0){ // compara com cd
        if(chdir(command[1]) < 0){
            perror("Não foi possível mudar de diretório");
        }
        freeStringVec(command, 2);
    }else if(strcmp(command[0], internal[1]) == 0){ //compara com exit
        while(!Vazia(listaDeProcessos)){
            kill(RetiraPrimeiro(listaDeProcessos), SIGUSR2); // Envia SIGUSR2 para todos os processos intermediarios
        }
        freeStringVec(command, 2);
        LiberaLista(listaDeProcessos);
        exit(0);
    }
}