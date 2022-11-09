#include "../shared/serv_cli_fifo.h"
#include "handlers_serv.h"

int main()
{
    // Declarations
    Request req;
    Response res;
    int req_flag;
    int res_flag;

    // Creation of named pipes
    if (mkfifo(FIFO1, 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create the FIFO1 file\n");
            exit(1);
        }
    }

    if (mkfifo(FIFO2, 0777) == -1)
    {
        if (errno != EEXIST)
        {
            printf("Could not create the FIFO2 file\n");
            exit(1);
        }
    }

    // Init random number generator
    srand(getpid());

    // Opening the named pipes
    int fifo1 = open(FIFO1, O_RDONLY);
    if (fifo1 == -1)
    {
        printf("Could not open the FIFO1 in mode read only from server\n");
        exit(1);
    }

    int fifo2 = open(FIFO2, O_WRONLY);
    if (fifo2 == -1)
    {
        printf("Could not open the FIFO2 in mode write only from server\n");
        exit(1);
    }

    // Install handlers
    signal(SIGUSR1, hand_reveil);
    signal(SIGUSR2, fin_serveur);

    // Core server code
    while (1)
    {
        // Read client request
        req_flag = read(fifo1, &req, sizeof(Request));
        if (req_flag == -1)
        {
            printf("Error occured while receiving request from the client\n");
            exit(2);
        }

        // Building response
        res.size = req.data;
        for (int i = 0; i < res.size; i++)
        {
            res.data[i] = (rand() % (UPPER - LOWER + 1)) + LOWER;
        }

        res.server_pid = getpid();

        // Send response to the client
        res_flag = write(fifo2, &res, sizeof(Response));
        if (res_flag == -1)
        {
            printf("Error occured while creating response for the client\n");
            exit(2);
        }

        // send SIGUSR1 to the user to be notified about the response construction
        kill(req.client_pid, SIGUSR1);

        // Pause the server until we get response from the client
        pause();
    }

    return 0;
}