#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define CLIENT "build/client"

int main()
{
    for (int i = 0; i < 2; i++)
    {
        // sleep(1);
        int clients_processes_flag = fork();
        if (clients_processes_flag == 0)
        {
            execl(CLIENT, "Client_Program", 0);
        }
    }

    return 0;
}