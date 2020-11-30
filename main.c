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
    struct sigaction chlTerm = {.sa_handler = chldTerm}; // Adiciona tratador para esperar um filho que tenha acabado
    sigemptyset(&chlTerm.sa_mask);
    sigaction(SIGCHLD, &chlTerm, NULL);
    TipoLista* ListaProcessos = CriaLista();
    char* line = NULL;
    while(1){
        int getlineRes = 0;
        size_t n = 0;
        line = NULL;
        while(getlineRes <= 1){
            if(!childExited){ // Evita printar acsh> mais uma vez caso um filho em background tenha terminado
                printf("acsh>");
                free(line);
                line = NULL;
            }else{
                childExited = 0;
            }
            getlineRes = getline(&line, &n, stdin);
            if(getlineRes == -1){ // Limpa indicadores do stdin após um sinal recebido
                clearerr(stdin);
            }
        }
        line[strlen(line) - 1] = '\0';// retira o \n que o getline adiciona
        trimLeft(line);
        trimRight(line);
        char** cmd = divideCmd(line);
        if(isInternal(cmd[0])){
            free(line);
            internalCommand(cmd, ListaProcessos);
            continue;
        }
        freeStringVec(cmd, 2);
        cmd = divideExtCmds(line);
        free(line);
        if(cmd[0][strlen(cmd[0]) - 1] == '%'){ // Verifica se existe um % no final do primeiro comando
            foregroundProcess(cmd[0]);
            freeStringVec(cmd, 5);
        }else{
            backgroundProcesses(cmd, ListaProcessos);
        }
    }

    return 0;
}