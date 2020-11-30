#include "../include/signalManipulation.h"

void chldTerm(int i){
    if(i == SIGCHLD){
        waitpid(-1, NULL, WNOHANG); // espera o processo intermediario que enviou o SIGCHLD
        childExited = 1;
    }
}

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

void setHandler(void (*handler)(int)){
    struct sigaction signals_handler = {.sa_handler = handler};
    sigemptyset(&signals_handler.sa_mask);
    sigaddset(&signals_handler.sa_mask, SIGINT);
    sigaddset(&signals_handler.sa_mask, SIGQUIT);
    sigaddset(&signals_handler.sa_mask, SIGTSTP);
    sigaction(SIGINT, &signals_handler, NULL);
    sigaction(SIGQUIT, &signals_handler, NULL);
    sigaction(SIGTSTP, &signals_handler, NULL);
}