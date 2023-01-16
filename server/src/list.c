#include "list.h"
#include <stdlib.h>
#include <string.h>


ClientList *addNode(int sockfd, char *ip)
{
    ClientList *client = (ClientList *)malloc(sizeof(ClientList));

    client->socket = sockfd;
    client->next = NULL;
    client->prev = NULL;
    client->leave_flag = 0;
    strncpy(client->role,"member",10);
    strncpy(client->ip,ip,16);
    strncpy(client->name,"NULL",5);
    return client;
}