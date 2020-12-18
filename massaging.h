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

void* readMessage(void* arg)
{
        int fd1;
        char * myfifo = "./myfifo";

        mkfifo(myfifo, 0666);
        char str1[80];
        while (!finishedProgram)
        {
            // First open in read only and read
            if (newMassage){

            fd1 = open(myfifo,O_RDONLY);
            read(fd1, str1, 80);

            // Print the read string and close
            while (isExecutingCommand);
            printf("\nnew massage : %s \n", str1);
            close(fd1);
            }
        }
       exit(0);
}

void sendMassage(char *msg){
    int fd;

    // FIFO file path
    char * myfifo = "./myfifo";

        mkfifo(myfifo, 0666);

        fd = open(myfifo, O_WRONLY);
        write(fd, msg, strlen(msg)+1);
        close(fd);
}
pthread_t ptid;

void createThread()
{
    pthread_create(&ptid, NULL, &readMessage, NULL);
}

void sleep(){

}