#ifndef _SIGNAL_MANIPULATION_H_
#define _SIGNAL_MANIPULATION_H_
#include <signal.h>
#include <stdio.h>
#include <sys/wait.h>

void chldTerm(int i);
void handleSignal(int i);
void setHandler(void (*handler)(int));

#endif