
#include <readline/readline.h>
#include <stdio.h>
#include <cstdlib>
#include <wait.h>
#include <unistd.h>
#include "command.h"


void executeCommand(char *command);

int main() {
    char *command;
    pid_t pid ;
    while (true) {
        command = readCommand();
        trimCommand(command);
        if (strlen(command)==0){
            continue;
        }
        pid = fork();
        if (pid == 0) {
            executeCommand(command);
        } else if(pid>0){
            int status;
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }else{
            printf("\nerror in fork process");
            break;
        }
    }
}

void executeCommand(char *command) {
    int spaceCount = getSplitedArrayLength(command);
    char *args[spaceCount];
    parseCommand(command, reinterpret_cast<char **>(&args));
    if ((execvp(args[0], args)) == -1) {
        printf("\ncommand not found");
    }
}


