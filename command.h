//
// Created by mrhb on 12/11/20.
//

#ifndef SHELL_READLINE_H
#define SHELL_READLINE_H
#define SINGLE_LINE_COMMAND 1
#define PIPE_LINE_COMMAND 2
#define QUIT 3
#define UNKNOWN_COMMAND 4
#define SEND_MSG 5
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
    if (contain(command,"msg")){
        return SEND_MSG;
    }else if (contain(command,"|")){
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

char *getShellNumber(){
    printf("\nif you are first shell enter (1) if not first enter (2)");
    char* shellNumber="3";
    printf("\nenter shell number : ");
    ssize_t bufSize = 0;
    if (getline(&shellNumber, reinterpret_cast<size_t *>(&bufSize), stdin)==-1){
        printf("\nGOOD BYE !!\n");
        exit(0);
    }
    shellNumber = strRemove(shellNumber, reinterpret_cast<const char *>("\n"));
    while (strcmp(shellNumber,"1")!=0 && strcmp(shellNumber,"2")!=0){
        printf("\ninvalid shell number\n");
        printf("if you are first shell enter (1) if not first enter (2)");
        printf("\nenter valid shell number again : ");
        ssize_t bufSize = 0;
        if (getline(&shellNumber, reinterpret_cast<size_t *>(&bufSize), stdin)==-1){
            printf("\nGOOD BYE !!\n");
            exit(0);
        }
        shellNumber = strRemove(shellNumber, reinterpret_cast<const char *>("\n"));
    }
    return shellNumber;
}



