#include "piperunner.h"
#define MAX_COMMANDS 10
#include <stdio.h>
#include <string.h>

int numCommands;

void preparePipe(char code[]){

    size_t len = strlen(code);
    if (len > 0 && code[len - 1] == '\n') {
        code[len - 1] = '\0';
    }

    char *commands[MAX_COMMANDS];
    char *token = strtok(code, "|");
    numCommands = 0;


    while (token != NULL && numCommands < MAX_COMMANDS) {
        commands[numCommands] = token;
        numCommands++;
        token = strtok(NULL, "|");
    }

    // Eliminar espacios en blanco alrededor de los comandos
    for (int i = 0; i < numCommands; ++i) {
        char *command = commands[i];
        while (*command == ' ') command++;
        commands[i] = command;
    }


    runPipe(commands, numCommands);
}



void runPipe(char *commands[], int cant){
    int pipe_fds[MAX_COMMANDS - 1][2];
    pid_t pids[MAX_COMMANDS];

    // Crear tuberías
    for (int i = 0; i < cant - 1; ++i) {
        if (pipe(pipe_fds[i]) == -1) {
            perror("Error creating pipe");
            exit(1);
        }
    }

    // Ejecutar comandos
    for (int i = 0; i < cant; ++i) {
        pids[i] = fork();

        if (pids[i] == -1) {
            perror("Error forking process");
            exit(1);
        }

        if (pids[i] == 0) {
            // Proceso hijo
            if (i > 0) {
                // Cerrar el descriptor de escritura de la tubería anterior en el proceso hijo
                close(pipe_fds[i - 1][1]);

                // Redirigir la entrada estándar al extremo de lectura de la tubería anterior
                dup2(pipe_fds[i - 1][0], STDIN_FILENO);
                close(pipe_fds[i - 1][0]);
            }

            if (i < cant - 1) {
                // Cerrar el descriptor de lectura de la tubería siguiente en el proceso hijo
                close(pipe_fds[i][0]);

                // Redirigir la salida estándar al extremo de escritura de la tubería actual
                dup2(pipe_fds[i][1], STDOUT_FILENO);
                close(pipe_fds[i][1]);
            }

            // Ejecutar el comando actual
            char *args[MAX_COMMANDS] = {0};
            char *token = strtok(commands[i], " ");
            int argCount = 0;

            while (token != NULL && argCount < MAX_COMMANDS - 1) {
                args[argCount] = token;
                argCount++;
                token = strtok(NULL, " ");
            }

            args[argCount] = NULL;

            execvp(args[0], args);

            // Si execvp falla
            perror("Error executing command");
            exit(1);
        }
    }

    // Cerrar los descriptores de archivo de la tubería en el proceso padre
    for (int i = 0; i < cant - 1; ++i) {
        close(pipe_fds[i][0]);
        close(pipe_fds[i][1]);
    }

    // Esperar a que todos los procesos hijos terminen
    for (int i = 0; i < cant; ++i) {
        waitpid(pids[i], NULL, 0);
    }
}