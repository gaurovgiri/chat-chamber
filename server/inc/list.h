#ifndef __LIST__
#define __LIST__


typedef struct Nodes
{
    int socket;
    struct Nodes *next;
    struct Nodes *prev;
    char ip[16];
    int leave_flag;
    int authenticated;
} ClientList;

extern ClientList *head, *curr;
ClientList *addNode(int,char *);

#endif // __LIST__