#include "server.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    int started;
    short port;
    signal(SIGINT, catch_ctrl_c_and_exit);

    if (argc <= 1)
    {
        printf("Please specify port: ./server <port>\n");
        return -1;
    }
    else if (argc > 2)
    {
        printf("More than 2 arguments passed: ./server <port>\n");
        return -1;
    }
    else
    {
        port = (short)atoi(argv[1]);
    }
    started = startServer(port);
    return 0;
}
