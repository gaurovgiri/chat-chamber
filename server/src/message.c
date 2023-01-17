#include "message.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>

void sendAll(ClientList *client, char *message)
{
    ClientList *tmp = (ClientList *)head->next;
    char sendMsg[123];
    sprintf(sendMsg,"%s: %s",client->username,message);
    while (tmp != NULL)
    {
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

char **parseCommand(char *message)
{

}