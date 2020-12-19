//
// Created by mrhb on 12/18/20.
//
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#ifndef SHELL_MASSAGING_H
#define SHELL_MASSAGING_H

#endif //SHELL_MASSAGING_H
pthread_t ptid;
char *shellNumber;
void *readMessage(void *arg) {
//    if (strcmp(shellNumber,"1")==0){
//        int fd;
//        char* myfifo = "./pipe/myfifo1";
//        char massage[512];
//        while(!finishedProgram)
//        {
//            sleep(1);
//            fd = open(myfifo, O_RDONLY);
//            if (read(fd, massage, 512) != -1){
//                printf("\nnew massage: %s\n", massage);
//                printf("mrhb_shell>>");
//            }
//            close(fd);
//        }
//        exit(0);
//
//    } else{
//        int fd;
//        char* myfifo = "./pipe/myfifo2";
//        char massage[512];
//        while(!finishedProgram)
//        {
//            sleep(1);
//            fd = open(myfifo, O_RDONLY);
//            if (read(fd, massage, 512) != -1){
//                printf("\nnew massage: %s\n", massage);
//            }
//            close(fd);
//        }
//        exit(0);
//    }
    if (strcmp("1",shellNumber)==0){
        int fd;
        char * myfifo = "./myfifo2";
        char massage[512],prev[512];
        while(!finishedProgram)
        {
            sleep(1);
            fd = open(myfifo, O_RDONLY);
         //   int t=read(fd, massage, 512);
            if (read(fd, massage, 512)!=-1){
                printf("\nnew massage: %s\n", massage);
                printf("mrhb_shell>>");
            }
            close(fd);
        }
        exit(0);

    } else{
        int fd;
        char * myfifo = "./myfifo1";
        char massage[512];

        while(!finishedProgram)
        {
            sleep(1);
            fd = open(myfifo, O_RDONLY);
           // int t=read(fd, massage, 512);
            if (read(fd, massage, 512)!=-1){
                printf("\nnew massage: %s\n", massage);
                printf("mrhb_shell>>");
            }
            close(fd);
        }
        exit(0);
    }
}


void sendMassage(char *msg) {
//    if (strcmp(shellNumber,"1")==0){
//        int fd;
//        char * myfifo = "./pipe/myfifo2";
//        mkfifo(myfifo, 0666);
//        fd = open(myfifo, O_WRONLY);
//        strRemove(msg,0);
//        strRemove(msg,1);
//        strRemove(msg,2);
//        int n = write(fd, msg, strlen(msg));
//        close(fd);
//        unlink(myfifo);
//    }else{
//        int fd;
//        char * myfifo = "./pipe/myfifo1";
//        mkfifo(myfifo, 0666);
//        fd = open(myfifo, O_WRONLY);
//        strRemove(msg,0);
//        strRemove(msg,1);
//        strRemove(msg,2);
//        write(fd, msg, strlen(msg));
//        close(fd);
//        unlink(myfifo);
//    }
    if (strcmp("1",shellNumber)==0){
        int fd;
        char * myfifo = "./myfifo1";
        mkfifo(myfifo, 0666);
        fd = open(myfifo, O_WRONLY);
        strRemove(msg,"msg");
        write(fd, msg, strlen(msg)+1);
        close(fd);
        unlink(myfifo);
    }else{
        int fd;
        char * myfifo = "./myfifo2";
        mkfifo(myfifo, 0666);
        fd = open(myfifo, O_WRONLY);
        strRemove(msg,"msg");
        write(fd, msg, strlen(msg)+1);
        close(fd);
        unlink(myfifo);
    }

}

void createThread() {
    pthread_create(&ptid, NULL, &readMessage, NULL);
}
