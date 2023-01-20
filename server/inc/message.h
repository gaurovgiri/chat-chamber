#ifndef __MESSAGE__
#define __MESSAGE__

#define MSG 0
#define CMD 1
#define JOIN 2
#define LEAVE 3
#define STOP 4

#include "client_handler.h"

/**
 * @brief creates a new structure that holds flag and message and sender username.
 * 
 */
typedef struct msg
{
    int flag;
    char sender[20];
    char msg[101];

} Message;

/**
 * @brief send message structure to all the clients
 * 
 * @param [client] point of ClientList that holds the information of conencted Clients
 * @param [message] object of Message that stores the  
 */
void sendAll(ClientList *, Message);


// void sendOne(List *, char *);


#endif // __MESSAGE__