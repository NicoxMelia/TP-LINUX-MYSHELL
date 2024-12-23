#ifndef SIGMANAGER_H
#define SIGMANAGER_H

#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include "jobid.h"

void sigchldHandler(int sg);
void sigtstpHandler(int sg);
void sigintHandler(int sg);
void sigquitHandler(int sg);
void ignoreSignal(int sg);


#endif