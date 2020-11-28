#ifndef _SYS_FUNCS_H_
#define _SYS_FUNCS_H_
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "signalManipulation.h"
#include "utils.h"
#include "listaencad.h"

/* Checa se um comando é interno ou não */
int isInternal(char* line);

/* Inicia os processos em backgroud */
void backgroundProcesses(char** commands, TipoLista* procs);

/* Inicia o processo em foreground */
void foregroundProcess(char* command);

/* Processa os comandos internos */
void internalCommand(char** command, TipoLista* listaDeProcessos);

#endif