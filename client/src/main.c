#include <ncurses.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "client.h"
#include "popup.h"
#include "ui.h"
#include "chat.h"

int main(int argc, char const *argv[])
{

    int connected;
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
    connectionStatus(connected = connectToServer(ip, port));

    if (connected == SUCCESS_0)
        loginOrReg();
    else
        exit(EXIT_0);



    if (!leaveFlag)
    {
        popup("Welcome to Chat", SUCCESS_0);
        pthread_t send_msg_thread;
        if (pthread_create(&send_msg_thread, NULL, (void *)send_msg_handler, NULL) != 0)
        {
            popup("Create pthread error", EXIT_0);
            exit(EXIT_FAILURE);
        }

        pthread_t recv_msg_thread;
        if (pthread_create(&recv_msg_thread, NULL, (void *)recv_msg_handler, NULL) != 0)
        {
            popup("Create pthread error", EXIT_0);
            exit(EXIT_FAILURE);
        }
    }

    while (true)
    {
        if (leaveFlag)
        {
            exit(EXIT_SUCCESS);
        }
    }

    endwin();
    return 0;
}