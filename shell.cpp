#include <readline/readline.h>
#include <cstdio>
#include "execute.h"



int main() {
    char *command;
    while (true) {
      if(!isExecutingCommand){
           command = readCommand();
           trim(command);
           if (strlen(command) == 0) {
               continue;
           }
           if (!execute(command)){
               if (!finishedProgram){
                   printf("command not found or not supported");
               }else{
                   printf("GOOD BYE !!");
                   exit(0);
               }
          }
       }
    }
}




