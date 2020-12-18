#include "execute.h"

int main(int argc, char **argv) {
    initKeyHandler();
    createThread();
    if (argc==2){
        executeBatchFile(argv[1]);
    }

    char *command;
    while (!finishedProgram) {
        usleep(2000);
        if(!isExecutingCommand){
           command = readCommand();
           lunch(command);
        }
    }
}




