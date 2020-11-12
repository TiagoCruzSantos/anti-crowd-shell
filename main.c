#include <stdio.h>
#include <stdlib.h>
#include "include/utils.h"
#include "include/signalManipulation.h"
#include "include/sysFuncs.h"

int main(int argc, char** argv){
    while(1){
        printf("acsh>");
        char* line = NULL;
        unsigned int n = 0;
        getline(&line, &n, stdin);
        line[strlen(line) - 1] = '\0';
        trimLeft(line);
        trimRight(line);
        char** cmd = divideCmd(line);
        if(isInternal(cmd[0])){
            internalCommand(cmd);
            printf("roda comando interno %s\n", cmd[0]);
            continue;
        }
        freeStringVec(cmd, 2);
        cmd = divideExtCmds(line);
        if(cmd[0][strlen(cmd[0]) - 1] == '%'){
            printf("foregroud\n");
            foregroundProcess(cmd[0]);
        }else{
            printf("background\n");
            backgroundProcesses(cmd);
        }
        for(int i = 0; i < 5 && cmd[i] != NULL; i++){
            printf("-%s-\n", cmd[i]);
        }
    }

    return 0;
}