#include "prompt.h"

void printPrompt(){
    char userName[1024];
    char hostName[1024];

    gethostname(userName, sizeof(userName));
    getlogin_r(hostName, sizeof(hostName));

    printf("%s@%s:%s$ ", userName, hostName, getenv("PWD"));
}