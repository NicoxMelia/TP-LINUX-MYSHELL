#ifndef RUNNER_H
#define RUNNER_H

#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "prompt.h"
#include "jobid.h"
#include "sigmanager.h"
#include <stdbool.h>

bool isPipe(char code[]);
int isInternal(char code[]);
void testMode(char code[]);
void start(char code[]);
void getCode(char code[], char aux[]);
void runInternal(char code[]);
void runExternal(char code[], bool bg);
void runForeground(char code[]);
void runBackground(char code[]);

#endif