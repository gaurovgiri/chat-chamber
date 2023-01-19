#include "message.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>

void sendAll(ClientList *client, char *message)
{
    ClientList *tmp = (ClientList *)head->next;
    char sendMsg[123];
    while (tmp != NULL)
    {
        sprintf(sendMsg,"%s: %s",(client->socket == tmp->socket ?"You":client->username),message);
        printf("Send to socket %d: \"%s\" \n", tmp->socket, message);
        send(tmp->socket, sendMsg, sizeof(sendMsg), 0);
        tmp = tmp->next;
    }
}

void sendOne(ClientList *client, char *message)
{
    printf("Send to socket %d: \"%s\" \n", client->socket, message);
    send(client->socket, message, sizeof(message), 0);
}
