#include "execute.h"


int main(int argc, char **argv) {

    if (argc==2){
        executeBatchFile(argv[1]);
    }

    char *command;
    while (!finishedProgram) {
      if(!isExecutingCommand){
           command = readCommand();
           lunch(command);
       }
    }
}




