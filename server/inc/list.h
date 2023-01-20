#ifndef __LIST__
#define __LIST__

#include "ssl.h"

/**
 * @brief creates a structure that stores the information of connected clients
 * 
 * 
 */
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

/**
 * @brief function to add new Client Nodes to ClientList (linkedlist);
 * 
 * @param [socket] socket file descriptor created for each new clients
 * 
 * @param [ip] ip address of the client
 *  
 * @return ClientList* 
 */
ClientList *addNode(int,char *);

#endif // __LIST__