#include "handlers_serv.h"
#include "../shared/serv_cli_fifo.h"

void hand_reveil(int sig){
    printf("Response receipt from client noticed by the server\n");
}

void fin_serveur(int sig)
{
    printf("Going to shut down the server\nGoing to delete FIFO used for server and client communication\n");
    unlink(FIFO1);
    unlink(FIFO2);
    exit(0);   
}