#include <ncurses.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/errno.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "client.h"
#include "popup.h"
#include "ssl.h"



SSL *ssl;

int sockfd, leaveFlag = 0;
struct sockaddr_in server_info, client_info;

void catch_ctrl_c_and_exit(int sig)
{
    exit(sig);
}

void cleanup()
{
    leaveFlag = 1;
    SSL_free(ssl);
    close(sockfd);
    SSL_CTX_free(ctx);
    endwin();
}

void serverPrompt(char ip[], short *port)
{
    printf("Connecting to Server: \n");
    printf("Server ip: ");
    scanf("%s", ip);
    printf("Port: ");
    scanf("%hd", port);
}

int connectToServer(char server_ip[], short server_port)
{

    SSL_library_init();

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    int err;
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);

    server_info.sin_family = AF_INET;
    server_info.sin_addr.s_addr = inet_addr(server_ip);
    server_info.sin_port = htons(server_port);

    InitCTX();

    err = connect(sockfd, (struct sockaddr *)&server_info, s_addrlen);
    if (err == -1)
    {
        return EXIT_0;
    }

    ssl = SSL_new(ctx);

    getsockname(sockfd, (struct sockaddr *)&client_info, (socklen_t *)&c_addrlen);
    getpeername(sockfd, (struct sockaddr *)&server_info, (socklen_t *)&s_addrlen);
    

    SSL_set_fd(ssl, sockfd);

    if (SSL_connect(ssl) == FAIL)
    {
        return EXIT_0;
    }
    else
    {

        return SUCCESS_0;
    }
}

char *getServerIP()
{
    return inet_ntoa(server_info.sin_addr);
}

uint16_t getServerPort()
{
    return ntohs(server_info.sin_port);
}
