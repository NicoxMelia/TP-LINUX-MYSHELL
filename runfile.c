#include "runfile.h"

void runFile(char fileName[]){
    FILE *file = fopen(fileName, "r");
    char code[1024];

    while(fgets(code, sizeof(code), file)){
        printf("readed line\n");
        start(code);
    }
    exit(0);
}