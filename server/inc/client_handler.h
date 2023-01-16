#ifndef __CLIENT_HANDLER__
#define __CLIENT_HANDLER__

#include "list.h"

void *c_handler(void *);
void sendAll(ClientList *,char *);
void closeSocket(ClientList *);

#endif // __CLIENT_HANDLER__