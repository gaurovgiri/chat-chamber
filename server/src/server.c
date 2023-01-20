#include "server.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include "list.h"
#include "client_handler.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include "ssl.h"

int s_sockfd, c_sockfd;
struct sockaddr_in server_info, client_info;
ClientList *head, *curr;

void catch_ctrl_c_and_exit(int sig)
{
    exit(sig);
}

void cleanup()
{
    ClientList *tmp = (ClientList *)head->next;
    Message msg;
    msg.flag = STOP;
    while (tmp != NULL)
    { 
        SSL_write(tmp->ssl,&msg,sizeof(msg));
        closeSocket(tmp);
        tmp = tmp->next;
    }
}

int startServer(short port)
{

    SSL_CTX *ctx;

    SSL_library_init();
    ctx = InitServerCTX();

    LoadCertificates(ctx, "certs/certi.pem", "certs/certi.pem");

    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);

    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);

    ClientList *client;

    s_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    server_info.sin_family = AF_INET;
    server_info.sin_port = htons(port);
    server_info.sin_addr.s_addr = INADDR_ANY;

    bind(s_sockfd, (struct sockaddr *)&server_info, s_addrlen);

    listen(s_sockfd, 5);

    getsockname(s_sockfd, (struct sockaddr *)&server_info, (socklen_t *)&s_addrlen);
    printf("Listening on %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));

    SSL *ssl;

    head = addNode(s_sockfd, inet_ntoa(server_info.sin_addr));
    curr = head;

    while (1)
    {
        c_sockfd = accept(s_sockfd, (struct sockaddr *)&client_info, (socklen_t *)&c_addrlen);

        getpeername(c_sockfd, (struct sockaddr *)&client_info, (socklen_t *)&c_addrlen);

        printf("Connecting with %s:%d\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));
        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, c_sockfd);
        client = addNode(c_sockfd, inet_ntoa(client_info.sin_addr));
        client->ssl = ssl;
        client->prev = (ClientList *)curr;
        curr->next = client;
        curr = client;

        pthread_t t_id;

        if (pthread_create(&t_id, NULL, c_handler, client) != 0)
        {
            perror("Creating Thread Unsuccessful");
            exit(EXIT_FAILURE);
        }
    }
}
