CC = g++
CFLAGS = -pthread -o

RMFLAGS = -rf
########################### Rules
all : main


main : shell.o
    $(CC) shell.o -o main

shell.o : shell.c CFLAGS
    $(CC) $(CFLAGS) shell.c
