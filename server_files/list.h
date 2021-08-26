#ifndef LIST
#define LIST

typedef struct Nodes
{
    int socket;
    struct Nodes *next;
    struct Nodes *prev;
    char ip[16];
    char name[31];
} ClientList;

ClientList *addNode(int sockfd, char *ip)
{
    ClientList *client = (ClientList *)malloc(sizeof(ClientList));
    
    client->socket = sockfd;
    client->next = NULL;
    client->prev = NULL;
    strncpy(client->ip,ip,16);
    strncpy(client->name,"NULL",5);
    return client;
}
#endif
volatile ClientList *head, *curr;