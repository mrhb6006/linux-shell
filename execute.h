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
#include "keyHandler.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

extern bool finishedProgram = false;
extern bool isExecutingCommand = false;


#endif

bool executeSingleLineCommand(char *command);

bool executePipeLineCommand(char *command);

bool execute(char *command);

bool execute(char *command) {
    bool result ;
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
        strRemove(command,"\n");
        int spaceCount = getSplitedArrayLength(command, " ");
        char *args[spaceCount];
        split(command, reinterpret_cast<char **>(&args), " ");
        if ((execvp(args[0], args)) == -1) {
            usleep(6000);
            isExecutingCommand= false;
            printf("command %s not found",args[0]);
            _exit(0);
        }
    } else if (pid > 0) {
        wait(0);
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
    strRemove(command,"\n");
    char *commands[2];
    int pipefd[2];
    int pid1=1,pid2=1;

    trim(command);
    split(command,commands,"|");

    pipe(pipefd);

    pid1=fork();
    if(0 == pid1){
        close(pipefd[1]);
        dup2(pipefd[0],STDIN_FILENO);
        trim(commands[1]);
        int spaceCount = getSplitedArrayLength(commands[1], " ");
        char *args[spaceCount];
        split(commands[1], reinterpret_cast<char **>(&args), " ");
        if ((execvp(args[0], args)) == -1) {
            printf("command %s not found",args[0]);
            _exit(0);
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
                printf("command %s not found",args[0]);
                _exit(0);
            }
        }else{
            usleep(8000);
            close(pipefd[0]);
            close(pipefd[1]);
            wait(0);
            wait(0);
            isExecutingCommand= false;
            return true;
        }
    }
}

bool lunch(char *command){
    trim(command);
    if (strlen(command) == 0) {
        return true;
    }
    if (!execute(command)){
        if (!finishedProgram){
            printf("command not found or not supported");
        }else{
            printf("GOOD BYE !! \n");
            exit(0);
        }
    }
    return true;
}

void executeBatchFile(char *fileName){
    FILE * batchFile;
    char * line = nullptr;
    size_t len = 0;
    batchFile = fopen(fileName, "r");
    if (batchFile == nullptr) {
        fprintf(stderr," \n file not found \n ");
        return;
    }
    while ((getline(&line, &len, batchFile)) != -1 && !finishedProgram) {
        if (strcmp(line,"\n")==0){
            continue;
        }
        printf("\n > %s",line);
        lunch(line);
        usleep(15000);
    }

    fclose(batchFile);
    if (line) {
        free(line);
    }
}