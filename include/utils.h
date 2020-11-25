#ifndef _UTILS_H_
#define _UTILS_H_
#include <string.h>
#include <stdlib.h>

char** divideExtCmds(char* input);
char** divideCmd(char* input);
char** formatCmd(char* input);
void freeStringVec(char** vec, int size);
void trimLeft(char* line);
void trimRight(char* line);

#endif