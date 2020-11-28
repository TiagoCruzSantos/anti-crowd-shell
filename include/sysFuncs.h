#ifndef _SYS_FUNCS_H_
#define _SYS_FUNCS_H_
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "signalManipulation.h"
#include "utils.h"
#include "listaencad.h"

int isInternal(char* line);
void backgroundProcesses(char** commands, TipoLista* procs);
void foregroundProcess(char* command);
void internalCommand(char** command, TipoLista* listaDeProcessos);

#endif