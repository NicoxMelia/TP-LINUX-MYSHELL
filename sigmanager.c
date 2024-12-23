#include"sigmanager.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

void sigchldHandler(int sg){
    waitpid(getJobId(), NULL, WUNTRACED);
}

void sigtstpHandler(int sg){
    kill(getJobId(), SIGTSTP);
}

void sigintHandler(int sg){
    kill(getJobId(), SIGINT);
}

void sigquitHandler(int sg){
    kill(getJobId(), SIGQUIT);
}

void ignoreSignal(int sg){
   // nothing
}