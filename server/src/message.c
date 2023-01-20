#include "message.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include "ssl.h"

void sendAll(ClientList *client, Message message)
{
    ClientList *tmp = (ClientList *)head->next;
    while (tmp != NULL && !(tmp->leave_flag))
    {
        printf("Send to socket %d: \"%s\" \n", tmp->socket, message.msg);
        if (tmp->socket == client->socket)
        {
            strncpy(message.sender, "You", sizeof("You"));
        }
        SSL_write(tmp->ssl, &message, sizeof(Message));
        tmp = tmp->next;
    }
}

void sendOne(ClientList *client, char *message)
{
    printf("Send to socket %d: \"%s\" \n", client->socket, message);
    send(client->socket, message, sizeof(message), 0);
}
