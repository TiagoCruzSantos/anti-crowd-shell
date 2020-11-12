#include "../include/sysFuncs.h"
const char* internal[] = {"cd", "exit"};

int isInternal(char* line){
    for(int i = 0; i < 2; i++){
        if(strcmp(line, internal[i]) == 0){
            return 1;
        }
    }
    return 0;
}

void backgroundProcesses(char** commands){

}

void foregroundProcess(char* commands){

}

void internalCommand(char** command){

}