#include <ncurses.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include "client.h"
#include "popup.h"

int sockfd;
struct sockaddr_in server_info, client_info;

void catch_ctrl_c_and_exit(int sig)
{
    exit(sig);
}

void cleanup()
{
    endwin();
}

void serverPrompt(char ip[], short *port)
{
    printw("Connecting to Server: \n");
    printw("Server ip: ");
    scanw("%s", ip);
    printw("Port: ");
    scanw("%hd", port);
}

int connectToServer(char server_ip[], short server_port)
{
    struct timeval tv;
    tv.tv_sec = 5;
    tv.tv_usec = 0;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    int err;
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);

    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = inet_addr(server_ip);
    server_info.sin_port = htons(server_port);

    err = connect(sockfd, (struct sockaddr *)&server_info, s_addrlen);
    setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(struct timeval));
    if (err == -1)
    {
        return EXIT_0;
    }

    getsockname(sockfd, (struct sockaddr *)&client_info, (socklen_t *)&c_addrlen);
    getpeername(sockfd, (struct sockaddr *)&server_info, (socklen_t *)&s_addrlen);

    return SUCCESS_0;
}

char *getServerIP()
{
    return inet_ntoa(server_info.sin_addr);
}

uint16_t getServerPort()
{
    return ntohs(server_info.sin_port);
}
