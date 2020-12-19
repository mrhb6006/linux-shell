#include "execute.h"

int main(int argc, char **argv) {
    initKeyHandler();

    shellNumber = getShellNumber();
    createThread();



    if (argc==2){
        executeBatchFile(argv[1]);
    }

    char *command;
    while (!finishedProgram) {
        usleep(2000);
        if(!isExecutingCommand){
           command = readCommand();
            if (strlen(command)>512){
                printf("command is long. max allowed length is 512 \n");
                continue;
            }
           lunch(command);
        }
    }
}




