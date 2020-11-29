#include "../include/utils.h"
#include <stdio.h>

void trimRight(char* line){
    for(int i = strlen(line) - 1; line[i] == ' '; i--){
        line[i] = '\0';
    }
}

void trimLeft(char* line){
    while(line[0] == ' '){
        for(int i = 0; line[i] != '\0'; i++){
            line[i] = line[i+1];
        }
    }
}

char *multi_tok(char *input, const char *delimiter) {
    static char *string;
    if (input != NULL)
        string = input;

    if (string == NULL)
        return string;

    char *end = strstr(string, delimiter);
    if (end == NULL) {
        char *temp = string;
        string = NULL;
        return temp;
    }

    char *temp = string;

    *end = '\0';
    string = end + strlen(delimiter);
    return temp;
}

char** formatCmd(char* input){
    char* inp2 = malloc(sizeof(char)*(strlen(input) + 1));
    strcpy(inp2, input);
    char* temp = inp2;
    char* token;
    // char** commands = malloc(sizeof(char*)*4);
    char** commands = calloc(4, sizeof(char*));
    for(int i = 0; i < 4; i++){
        token = multi_tok(temp, " ");
        temp = NULL;
        if(token == NULL || token[0] == '%'){
            commands[i] = NULL;
            break;
        }
        if(token[strlen(token) - 1] == '\n'){
            token[strlen(token) - 1] = '\0';
        }
        trimLeft(token);
        trimRight(token);
        commands[i] = malloc(sizeof(char)*(strlen(token) + 1));
        strcpy(commands[i], token);
    }
    free(inp2);
    return commands;
}

char** divideExtCmds(char* input){
    char* inp2 = malloc(sizeof(char)*(strlen(input) + 1));
    strcpy(inp2, input);
    char* temp = inp2;
    char* token;
    //char** commands = malloc(sizeof(char*)*5);
    char** commands = calloc(5, sizeof(char*));
    for(int i = 0; i < 5; i++){
        token = multi_tok(temp, "<3");
        temp = NULL;
        if(token == NULL){
            commands[i] = NULL;
            break;
        }
        if(token[strlen(token) - 1] == '\n'){
            token[strlen(token) - 1] = '\0';
        }
        trimLeft(token);
        trimRight(token);
        commands[i] = malloc(sizeof(char)*(strlen(token) + 1));
        strcpy(commands[i], token);
    }
    free(inp2);
    return commands;
}

char** divideCmd(char* input){
    char* inp2 = malloc(sizeof(char)*(strlen(input) + 1));
    strcpy(inp2, input);
    char* temp = inp2;
    char* token;
    //char** command = malloc(sizeof(char*)*2);
    char** command = calloc(2, sizeof(char*));
    for(int i = 0; i < 2; i++){
        token = multi_tok(temp, " ");
        temp = NULL;
        if(token == NULL){
            command[i] = NULL;
            break;
        }
        if(token[strlen(token) - 1] == '\n'){
            token[strlen(token) - 1] = '\0';
        }
        trimLeft(token);
        trimRight(token);
        command[i] = malloc(sizeof(char)*(strlen(token) + 1));
        strcpy(command[i], token);
    }
    free(inp2);
    return command;
}

void freeStringVec(char** vec, int size){
    for(int i = 0; i < size; i++){
        if(vec[i] != NULL){
           free(vec[i]); 
        }
    }
    free(vec);
}