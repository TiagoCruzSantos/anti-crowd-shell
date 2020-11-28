#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include "include/utils.h"
#include "include/signalManipulation.h"
#include "include/sysFuncs.h"
#include "include/listaencad.h"

int main(){
    childExited = 0;
    setHandler(handleSignal);
    struct sigaction chlTerm;
    chlTerm.sa_handler = chldTerm;
    sigemptyset(&chlTerm.sa_mask);
    sigaction(SIGCHLD, &chlTerm, NULL);
    TipoLista* ListaProcessos = CriaLista();
    char* line = NULL;
    while(1){
        //printf("%p\n", ListaProcessos);
        //ImprimeLista(ListaProcessos);
        int getlineRes = 0;
        size_t n = 0;
        line = NULL;
        while(getlineRes <= 1){
            if(!childExited){
                printf("acsh>");
            }else{
                childExited = 0;
            }
            getlineRes = getline(&line, &n, stdin);
            if(getlineRes == -1){
                clearerr(stdin);
            }
        }
        line[strlen(line) - 1] = '\0';
        trimLeft(line);
        trimRight(line);
        char** cmd = divideCmd(line);
        if(isInternal(cmd[0])){
            internalCommand(cmd, ListaProcessos);
            continue;
        }
        freeStringVec(cmd, 2);
        cmd = divideExtCmds(line);
        // printf("%s\n", getcwd(s, 100));
        if(cmd[0][strlen(cmd[0]) - 1] == '%'){
            foregroundProcess(cmd[0]);
        }else{
            //printf("background\n");
            backgroundProcesses(cmd, ListaProcessos);
        }
        free(line);
        //printf("");
        // for(int i = 0; i < 5 && cmd[i] != NULL; i++){
        //     printf("-%s-\n", cmd[i]);
        // }
    }

    return 0;
}