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
            finishedProgram = true;
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
            return false;
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
//    char *commands[2];
//    trim(command);
//    split(command,commands,"|");
//    int pipefd[2];
//    pid_t p1, p2;
//    if (pipe(pipefd) < 0) {
//        printf("\nPipe could not be initialized");
//        return true;
//    }
//    p1 = fork();
//    if (p1 < 0) {
//        printf("\nCould not fork");
//        return true;
//    }
//
//    if (p1 == 0) {
//        // Child 1 executing..
//        // It only needs to write at the write end
//        close(pipefd[0]);
//        dup2(pipefd[1], STDOUT_FILENO);
//        close(pipefd[1]);
//        trim(commands[0]);
//        int spaceCount = getSplitedArrayLength((commands[0]), " ");
//        char *args[spaceCount];
//        split((commands[0]), reinterpret_cast<char **>(&args), " ");
//        if ((execvp(args[0], args)) == -1) {
//            return false;
//        }
//    } else {
//        // Parent executing
//        p2 = fork();
//
//        if (p2 < 0) {
//            printf("\nCould not fork");
//            return true;
//        }
//
//        // Child 2 executing..
//        // It only needs to read at the read end
//        if (p2 == 0) {
//            close(pipefd[1]);
//            dup2(pipefd[0], STDIN_FILENO);
//            close(pipefd[0]);
//            trim(commands[1]);
//            int spaceCount = getSplitedArrayLength(commands[1], " ");
//            char *args[spaceCount];
//            split(commands[1], reinterpret_cast<char **>(&args), " ");
//            if ((execvp(args[0], args)) == -1) {
//                return false;
//            }
//        } else {
//            int status;
//            do {
//                waitpid(p2, &status, WUNTRACED);
//            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
//            return true;
//        }
//    }
//    return false;

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
                return false;
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
                return false;
            }
        }else{
            int status;
            do {
           waitpid(pid2, &status, WUNTRACED);
         } while (!WIFEXITED(status) && !WIFSIGNALED(status));
            close(pipefd[0]);
            close(pipefd[1]);
            isExecutingCommand= false;
            return true;
        }
    }
}
