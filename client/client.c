#include "../shared/serv_cli_fifo.h"
#include "handlers_cli.h"

int main(int argc, char *argv[])
{
    // Declaration
    Request req;
    Response res;
    int req_flag;
    int res_flag;
    int data;

    // Opening the named pipes
    int fifo1 = open(FIFO1, O_WRONLY);
    if (fifo1 == -1)
    {
        printf("Could not open the FIFO1 in mode read only from client\n");
        exit(1);
    }

    int fifo2 = open(FIFO2, O_RDONLY);
    if (fifo2 == -1)
    {
        printf("Could not open the FIFO2 in mode write only from client\n");
        exit(1);
    }

    // Installing handlers
    signal(SIGUSR1, hand_reveil);

    // Init random number generator
    srand(getpid());

    // Building request
    data = (rand() % (UPPER - LOWER + 1)) + LOWER;
    printf("Random number generated (client side): %d\n", data);
    req.data = data;
    req.client_pid = getpid();

    // Sending request
    req_flag = write(fifo1, &req, sizeof(Request));
    if (req_flag == -1)
    {
        printf("Error occured while creating request\n");
        exit(2);
    }

    // Pausing the client and waiting for the response from the server
    pause();

    // Reading the answer from the server
    res_flag = read(fifo2, &res, sizeof(Response));
    if (res_flag == -1)
    {
        printf("Error occured while receiving response from the server\n");
        exit(2);
    }

    // Send SIGUSR1 to notify the server that the response is received successfully
    kill(res.server_pid, SIGUSR1);

    // Manage the response
    printf("Random numbers generated by the server:\n");
    for (size_t i = 0; i < res.size; i++)
    {
        printf("%d \t", res.data[i]);
    }
    printf("\n");

    // (Optional) by passing an argument to this clinet you can stop the server
    if(argc >= 2){
        // User passed extra args to this program
        if(strcmp(argv[1], "-s") == 0){
            kill(res.server_pid, SIGUSR2);
        }
    }

    //close(fifo1);
    //close(fifo2);

    return 0;
}