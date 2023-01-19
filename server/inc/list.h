#ifndef __LIST__
#define __LIST__

#include "ssl.h"
typedef struct Nodes
{
    int socket;
    struct Nodes *next;
    struct Nodes *prev;
    char ip[16];
    char username[20];
    int role;
    int leave_flag;
    int authenticated;
    SSL *ssl;
} ClientList;

extern ClientList *head, *curr;
ClientList *addNode(int,char *);

#endif // __LIST__