//
// Created by mrhb on 12/14/20.
//

#ifndef SHELL_EXECUTE_H
#define SHELL_EXECUTE_H
#include <cstdlib>
#include <wait.h>
#include <unistd.h>
#include <cstdio>
#include "command.h"
extern bool finished = false;

#endif //SHELL_EXECUTE_H

bool executeSingleLineCommand(char *command);
bool executePipeLineCommand(char *command);
bool execute(char *command);

bool execute(char *command) {
    bool result=false;
    int type = getCommandType(command);
    switch (type) {
        case SINGLE_LINE_COMMAND:
            result = executeSingleLineCommand(command);
            break;
        case PIPE_LINE_COMMAND:
            result=executePipeLineCommand(command);
            break;
        case QUIT :
            finished = true;
        default:
            result= false;
    }
    return result;
}

bool executeSingleLineCommand(char *command) {
    pid_t  pid;
    pid = fork();
    if (pid == 0) {
        trim(command);
        int spaceCount = getSplitedArrayLength(command, " ");
        char *args[spaceCount];
        split(command, reinterpret_cast<char **>(&args), " ");
        if ((execvp(args[0], args)) == -1) {
            printf("\ncommand not found");
        }
    } else if (pid > 0) {
        int status;
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        return true;
    } else {
        return false;
    }
}

bool executePipeLineCommand(char *command) {
    //to do
    return false;
}