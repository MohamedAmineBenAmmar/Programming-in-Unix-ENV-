#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define SERVER "build/server"
#define CLIENT "build/client"

int main()
{
    printf("test \n");

    for (size_t i = 0; i < 2; i++)
    {
        int clients_processes_flag = fork();
        if (clients_processes_flag == 0)
        {
            execl(CLIENT, "Client Program", 0);
        }
    }

    return 0;
}