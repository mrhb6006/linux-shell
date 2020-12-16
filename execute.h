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
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern bool finishedProgram = false;
extern bool isExecutingCommand = false;


#endif //SHELL_EXECUTE_H

bool executeSingleLineCommand(char *command);

bool executePipeLineCommand(char *command);

bool execute(char *command);

bool execute(char *command) {
    bool result = false;
    int type = getCommandType(command);
    switch (type) {
        case SINGLE_LINE_COMMAND:
            result = executeSingleLineCommand(command);
            break;
        case PIPE_LINE_COMMAND:
            result = executePipeLineCommand(command);
            break;
        case QUIT :
            finishedProgram = true;
        default:
            result = false;
    }
    return result;
}

bool executeSingleLineCommand(char *command) {
    isExecutingCommand= true;
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        trim(command);
        int spaceCount = getSplitedArrayLength(command, " ");
        char *args[spaceCount];
        split(command, reinterpret_cast<char **>(&args), " ");
        if ((execvp(args[0], args)) == -1) {
            usleep(6000);
            isExecutingCommand= false;
            return false;
        }
    } else if (pid > 0) {
        int status;
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        usleep(6000);
        isExecutingCommand= false;
        return true;
    } else {
        usleep(6000);
        isExecutingCommand= false;
        return false;
    }
}

bool executePipeLineCommand(char *command) {
    isExecutingCommand= true;
    strRemove(command,"\"");
    char *commands[2];
    trim(command);
    split(command,commands,"|");
    int pipefd[2];
    int pid1=1,pid2=1;
    pipe(pipefd);
    pid1=fork();
    if(0 == pid1){
        //parent
        close(pipefd[1]);
        dup2(pipefd[0],STDIN_FILENO);
        trim(commands[1]);
        int spaceCount = getSplitedArrayLength(commands[1], " ");
        char *args[spaceCount];
        split(commands[1], reinterpret_cast<char **>(&args), " ");
        if ((execvp(args[0], args)) == -1) {
            printf("command not found or not supported");
            exit(0);
        }
    }else{
        pid2 = fork() ;
        if (pid2 == 0){
            close(pipefd[0]);
            dup2(pipefd[1],STDOUT_FILENO);
            trim(commands[0]);
            int spaceCount = getSplitedArrayLength((commands[0]), " ");
            char *args[spaceCount];
            split((commands[0]), reinterpret_cast<char **>(&args), " ");
            if ((execvp(args[0], args)) == -1) {
                printf("command not found or not supported");
                exit(0);
            }
        }else{
            int status1;
            do {
                waitpid(pid2, &status1, WUNTRACED);
            } while ((!WIFEXITED(status1) && !WIFSIGNALED(status1)));
            usleep(10000);
            close(pipefd[0]);
            close(pipefd[1]);
            isExecutingCommand= false;
            return true;
        }
    }
}
