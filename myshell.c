#include "prompt.h"
#include "runfile.h"
#include "jobid.h"

int main(int argc, char *argv[]){

    char code[1024];

    if(argc == 2){
        runFile(argv[1]);
    }else{
        while(1){
            printPrompt();
            fgets(code, sizeof(code), stdin);
            start(code);
        }
    }

    return 0;

}