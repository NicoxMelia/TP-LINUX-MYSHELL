#include "runner.h"
#include "piperunner.h"

bool isPipe(char code[]){
    return strchr(code, '|');
}

bool isRedirection(char code[]){
    return (strchr(code, '>') || strchr(code, '<'));
}


int isInternal(char code[]){
    char *internals[] = {"cd", "clr", "echo", "quit"};
    for(int i=0; i<4; i++){
        if(strstr(code, internals[i]) != NULL){
            return 1;
        }
    }
    return 0;
}

void start(char code[]){
    if(strstr(code, "clr") != NULL){
        __pid_t pclear = fork();
        if(pclear == 0){
            execl("/usr/bin/clear", "clear", NULL);
        }else{
            wait(NULL);
        }
    }else{
        testMode(code);
    }
}

void getCode(char code[], char aux[]){
    sscanf(code, "%[^&]", aux);
}

void testMode(char code[]){

    char aux[1024];
    getCode(code, aux);


    if(isPipe(code)){
        preparePipe(code);
    }else if(isInternal(code)){

        if(strchr(code, '&') != NULL){
            runBackground(aux);
        }else{
            runForeground(code);
        }
    }else{
        if(strchr(code, '&') != NULL){
            runExternal(aux, true);
        }else{
            runExternal(aux, false);
        }
    }


}

void runForeground(char code[]){
    runInternal(code);
}

void runBackground(char code[]){
    __pid_t pId = fork();
    if(pId == 0){
        runInternal(code);
        exit(0);
    }else{
        wait(NULL);
    }
}

void runExternal(char code[], bool bg){

   code[strcspn(code, "\n")] = 0;

   char *args[64];
   int i = 0;
   pid_t idExt;

    char *token = strtok(code, " ");
    while (token != NULL && i < 63) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    idExt = fork();

    if(idExt == 0){
        if (execvp(args[0], args) == -1) {
            perror("There was an error running this command\n");
        }

    }else{
        setJobId(idExt);
        if(!bg){
            signal(SIGCHLD, sigchldHandler);
            signal(SIGINT, sigintHandler);
            signal(SIGQUIT, sigquitHandler);
            signal(SIGTSTP, sigtstpHandler);
            wait(NULL);
        }
    }
}

void runInternal(char code[]){
    char dir[1024];
    char phrase[1024];


    if(sscanf(code, "cd %s", dir) == 1){

        if(strcmp(code, "cd -\n") == 0){
            chdir(getenv("OLDPWD"));
            setenv("PWD", getcwd(NULL, 0), 1);
            return;
        }

        setenv("OLDPWD", getcwd(NULL, 0), 1);

        if(chdir(dir) != 0){
            printf("There was an error trying to change directory %s\n", dir);
        }else{
            setenv("PWD", getcwd(NULL, 0), 1);
        }

    }else if(strcmp(code, "cd\n") == 0){
        chdir(getenv("HOME"));
        setenv("PWD", getcwd(NULL, 0), 1);
        
    }else if(strcmp(code, "quit\n") == 0){
        exit(0);
    }else if(sscanf(code, "echo %[^\n]", phrase) == 1){
        if(strchr(phrase, '|')){
            char phraseAux[1024];
            char varEnv[1024];
            sscanf(phrase, "%[^|]|", phraseAux);
            sscanf(phraseAux, "%[^|]", phraseAux);
            sscanf(phrase, "%*[^|]| %s", varEnv);
            printf("%s, %s\n", phraseAux, getenv(varEnv));
            
        }else{
            printf("%s\n", phrase);
        }
    }


}