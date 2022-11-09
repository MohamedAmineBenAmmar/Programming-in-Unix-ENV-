#include "handlers_cli.h"
#include "../shared/serv_cli_fifo.h"

void hand_reveil(int sig){
    printf("Received an appropriate response from the server\n");
}
