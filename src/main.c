#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "client.h"
#include "popup.h"



int main(int argc, char const *argv[])
{
    signal(SIGINT, catch_ctrl_c_and_exit);
    initscr();
    atexit(cleanup);

    char ip[17];
    short port;

    if (argc <= 1)
    {
        serverPrompt(ip, &port);
    }
    else if (argc == 2)
    {
        printf("Please specify both ip and port: ./client <ip> <port>");
        exit(EXIT_0);
    }
    else if (argc >= 3)
    {
        strncpy(ip, argv[1], sizeof(ip));
        port = (short)atoi(argv[2]);
    }
    refresh();
    connectionStatus(connectToServer(ip,port));

    
    
    endwin();
    return 0;
}