#ifndef _SIGNAL_MANIPULATION_H_
#define _SIGNAL_MANIPULATION_H_
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

/* Se torna 1 toda vez que um processo intermediario entre o acsh e os filhos em backgroud terminar */
int childExited;

/* Espera por processos intermediários que acabaram */
void chldTerm(int i);

/* Trata dos sinais SIGINT, SIGQUIT e SIGTSTP*/
void handleSignal(int i);

/* Adiciona um tratador para os sinis SIGINT, SIGQUIT e SIGTSTP */
void setHandler(void (*handler)(int));

#endif