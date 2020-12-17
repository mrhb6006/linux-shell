//
// Created by mrhb on 12/11/20.
//

#ifndef SHELL_READLINE_H
#define SHELL_READLINE_H
#define SINGLE_LINE_COMMAND 1
#define PIPE_LINE_COMMAND 2
#define QUIT 3
#define UNKNOWN_COMMAND 4
#endif
#include <cstring>
#include "stringUtils.h"

char *readCommand() {
    printf("\nmrhb_shell>>");
    char *line = NULL;
    ssize_t bufSize = 0;
    if (getline(&line, reinterpret_cast<size_t *>(&bufSize), stdin)==-1){
        printf("\nGOOD BYE !!\n");
        exit(0);
    }
    line = strRemove(line, reinterpret_cast<const char *>("\n"));

    return line;
}

int getCommandType(char *command){
    if (contain(command,"|")){
        if (countOfSubSting(command,"|")!=1){
            return UNKNOWN_COMMAND;
        }
        return PIPE_LINE_COMMAND;
    }else if (contain(command,"quit")){
        return QUIT;
    }else {
        return SINGLE_LINE_COMMAND;
    }
}





