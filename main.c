#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "include/utils.h"
#include "include/signalManipulation.h"
#include "include/sysFuncs.h"


int main(){
    setHandler(handleSignal);
    struct sigaction chlTerm;
    chlTerm.sa_handler = chldTerm;
    sigemptyset(&chlTerm.sa_mask);
    sigaction(SIGCHLD, &chlTerm, NULL);
    while(1){
        printf("acsh>");
        char* line = NULL;
        size_t n = 0;
        getline(&line, &n, stdin);
        if(line == NULL){
            clearerr(stdin);
            rewind(stdin);
            continue;
        }
        line[strlen(line) - 1] = '\0';
        if(strlen(line) == 0){
            free(line);
            clearerr(stdin);
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
            //printf("background\n");
            backgroundProcesses(cmd);
        }
        // for(int i = 0; i < 5 && cmd[i] != NULL; i++){
        //     printf("-%s-\n", cmd[i]);
        // }
    }

    return 0;
}