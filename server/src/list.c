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
    client->authenticated = 0;
    strncpy(client->ip,ip,16);
    return client;
}