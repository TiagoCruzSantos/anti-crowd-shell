#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "include/utils.h"
#include "include/signalManipulation.h"
#include "include/sysFuncs.h"

// void sigchl(int i){
//     printf("crianza moree\n");
// }

int main(){
    struct sigaction signals_handler = {.sa_handler = handleSignal};
    //struct sigaction foregroundCHandler = {.sa_handler = sigchl};
    sigemptyset(&signals_handler.sa_mask);
    //sigemptyset(&foregroundCHandler.sa_mask);
    sigaddset(&signals_handler.sa_mask, SIGINT);
    sigaddset(&signals_handler.sa_mask, SIGQUIT);
    sigaddset(&signals_handler.sa_mask, SIGTSTP);
    sigaction(SIGINT, &signals_handler, NULL);
    sigaction(SIGQUIT, &signals_handler, NULL);
    sigaction(SIGTSTP, &signals_handler, NULL);
    //sigaction(SIGCHLD, &foregroundCHandler, NULL);

    while(1){
        printf("acsh>");
        char* line = NULL;
        size_t n = 0;
        getline(&line, &n, stdin);
        if(line == NULL){
            rewind(stdin);
            getline(&line, &n, stdin);
        }
        line[strlen(line) - 1] = '\0';
        if(strlen(line) == 0){
            free(line);
            continue;
        }
        trimLeft(line);
        trimRight(line);
        char** cmd = divideCmd(line);
        if(isInternal(cmd[0])){
            internalCommand(cmd);
            continue;
        }
        freeStringVec(cmd, 2);
        cmd = divideExtCmds(line);
        char *s;
        // printf("%s\n", getcwd(s, 100));
        if(cmd[0][strlen(cmd[0]) - 1] == '%'){
            foregroundProcess(cmd[0]);
        }else{
            printf("background\n");
            backgroundProcesses(cmd);
        }
        // for(int i = 0; i < 5 && cmd[i] != NULL; i++){
        //     printf("-%s-\n", cmd[i]);
        // }
    }

    return 0;
}