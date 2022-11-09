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

    int serv_fork = fork();
    if (serv_fork == 0)
    {
        execl(SERVER, "Server Program", 0);
    }

    if (serv_fork > 0)
    {
        for (size_t i = 0; i < 1; i++)
        {
            int clients_processes_flag = fork();
            if (clients_processes_flag == 0)
            {
                execl(CLIENT, "Client Program", 0);
            }
        }
    }

    return 0;
}