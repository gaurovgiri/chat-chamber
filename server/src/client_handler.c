#include "client_handler.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>

void sendAll(ClientList *client, char *msg)
{
    ClientList *tmp = (ClientList *)head->next;
    while (tmp != NULL)
    {

        printf("Send to socket %d: \"%s\" \n", tmp->socket, msg);
        send(tmp->socket, msg, 101, 0);
        tmp = tmp->next;
    }
}

void *c_handler(void *client_t)
{
    ClientList *client = (ClientList *)client_t;
    char msg[101];

    while (1)
    {
        memset(msg, 0, sizeof(msg));
        recv(client->socket, msg, sizeof(msg), 0);
        if (strcmp(msg, "/exit") == 0)
        {
            break;
        }
        else
        {
            sendAll(client, msg);
        }
    }
    closeSocket(client);
}

void closeSocket(ClientList *client)
{
    close(client->socket);
    if (client == curr)
    {
        curr = client->prev;
        curr->next = NULL;
    }
    else
    {
        client->prev->next = client->next;
        client->next->prev = client->prev;
    }
    free(client);
}