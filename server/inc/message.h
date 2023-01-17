#ifndef __MESSAGE__
#define __MESSAGE__

#define MSG 0
#define CMD 1

#include "client_handler.h"

typedef struct msg
{
    int flag;
    char msg[101];
} Message;


void sendAll(ClientList *, char *);
void sendOne(ClientList *, char *);
char **parseCommand(char *);

#endif // __MESSAGE__