#ifndef _UTILS_H_
#define _UTILS_H_
#include <string.h>
#include <stdlib.h>

/* Separa os comandos externos em "<3" */
char** divideExtCmds(char* input);

/* Divide um comando interno */
char** divideCmd(char* input);

/* Divide um comando externo */
char** formatCmd(char* input);

/* Libera um vetor de strings */
void freeStringVec(char** vec, int size);

/* Retira os espaços a esquerda */
void trimLeft(char* line);

/* Retira os espaços a direita */
void trimRight(char* line);

#endif