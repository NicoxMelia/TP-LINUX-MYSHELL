#ifndef PIPERUNNER_H
#define PIPERUNNER_H
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

extern int numCommands;


void preparePipe(char code[]);
void runPipe(char *commands[], int numCommands);
//void redirection(char *commands[], int num_commands);


#endif