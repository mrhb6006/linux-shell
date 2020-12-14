//
// Created by mrhb on 12/11/20.
//
#ifndef SHELL_READLINE_H
#define SHELL_READLINE_H
#endif //SHELL_READLINE_H
#include <cstring>
#include "stringUtils.h"

char *readCommand() {
    printf("\nmrhb_shell>>");
    char *line = NULL;
    ssize_t bufSize = 0;
    getline(&line, reinterpret_cast<size_t *>(&bufSize), stdin);
    line = strRemove(line, reinterpret_cast<const char *>("\n"));
    return line;
}

void parseCommand(char* cmd ,char **args) {
    int n=0;
    char *command;
    while( (command=strsep(&cmd," ")) != NULL ){
        args[n++]=command;
    }
    args[n]=NULL;
}


char* trimCommand(char *command){
    for (int i = 0; command[i] ; ++i) {
        if (i!=0 && i!=(strlen(command)-1)){
            if (command[i]==' ' && (command[i-1]==' ' || command[i+1]==' ')){
                strRemove(command,i);
                i--;
            }
        }else if(i==0){
            if (command[0]==' '){
                strRemove(command,0);
                i--;
            }
        }else{
            if (command[i]==' ' && i==strlen(command)-1){
                strRemove(command,i);
            }
        }
    }
    return command;
}


