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
    int connectionStatus = connectToServer(ip, port);
    refresh();
    char msg[50];
    if (connectionStatus == SUCCESS_0)
    {
        snprintf(msg, sizeof(msg), "Successfully Connected to %s:%d", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
        popup(msg, SUCCESS_POPUP);
    }
    else if (connectionStatus == EXIT_0)
    {

        snprintf(msg, sizeof(msg), "Couldn't Connected to %s:%d", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
        popup(msg, ERROR_POPUP);
    }

    endwin();
    return 0;
}