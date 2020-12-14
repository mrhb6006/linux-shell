#include <readline/readline.h>
#include <cstdio>
#include "execute.h"



int main() {
    char *command;
    while (true) {
        command = readCommand();
        trim(command);
        if (strlen(command) == 0) {
            continue;
        }
        if (!execute(command)){
            if (!finished){
                printf("command not found or not supported");
            }else{
                printf("GOOD BYE !!");
                break;
            }
        }
    }
}




