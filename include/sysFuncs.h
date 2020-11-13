#ifndef _SYS_FUNCS_H_
#define _SYS_FUNCS_H_
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "signalManipulation.h"
#include "utils.h"

int isInternal(char* line);
void backgroundProcesses(char** commands);
void foregroundProcess(char* command);
void internalCommand(char** command);

#endif