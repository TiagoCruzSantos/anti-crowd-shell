#include "../include/signalManipulation.h"

void handleSignal(int i){
    switch(i){
        case SIGINT:
            printf("Não adianta me enviar o sinal por Ctrl-C . Estou vacinado!!\n");
            break;
        case SIGQUIT:
            printf("Não adianta me enviar o sinal por Ctrl-\\ . Estou vacinado!!\n");
            break;
        case SIGTSTP:
            printf("Não adianta me enviar o sinal por Ctrl-Z . Estou vacinado!!\n");
            break;
    }
}