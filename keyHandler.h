//
// Created by mrhb on 12/17/20.
//

#ifndef SHELL_KEYHANDLER_H
#define SHELL_KEYHANDLER_H

#endif //SHELL_KEYHANDLER_H

//
//#include <unistd.h>
//#include <cstdio>
//#include <termios.h>
//#include <csignal>
//
//void Ctrl_D_handler(int sig){
//     printf("asasasas");
//    //exit(0);
//}
//
//
//
//#include <stdlib.h>
//#include <string.h>
//#include <stdbool.h>
//#include <setjmp.h>
//
//static volatile sig_atomic_t jmp_set;
//
//static void ctrlc_handler(int signal) {
//    if (jmp_set == 0)
//        return;
//    if (signal == SIGINT) {
//    }
//}
//
//void initKeyHandler(){
//    // signal(SIGINT,Ctrl_D_handler);
//    if (signal(SIGINT, ctrlc_handler) == SIG_ERR) {
//        perror("signal error");
//        exit(1);
//    }
//    jmp_set = 1;
//}

#include <unistd.h>
#include <stdio.h>
#include <termios.h>
#include <signal.h>

void CTRL_C_handler(int sig){
    printf("\n");
}

int initKeyHandler(){
    signal(SIGINT,CTRL_C_handler);
}
