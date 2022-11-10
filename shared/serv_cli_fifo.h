#ifndef SHARED_HEADER_FILE
#define SHARED_HEADER_FILE

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#include <signal.h>

#include <string.h>

// Macros and paths definition

#define NMAX 50
#define FIFO1 "named-pipes/fifo1"
#define FIFO2 "named-pipes/fifo2"
#define LOWER 1
#define UPPER NMAX

// Types definition

typedef struct Request
{
    int data;
    int client_pid;
} Request;

typedef struct Response
{
    int data[NMAX];
    int size;
    int server_pid;
} Response;

#endif