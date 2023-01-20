#include "server.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <db.h>
#include <string.h>
#include "ssl.h"

int main(int argc, char const *argv[])
{
    if (!isRoot())
    {
        printf("This program must be run as root/sudo user!!");
        exit(0);
    }

    int started;
    short port;
    atexit(cleanup);
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

    initDB();
    started = startServer(port);
    return 0;
}
