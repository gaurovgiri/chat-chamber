#ifndef __DB__
#define __DB__

#define AUTH_SUCCESS 1
#define AUTH_FAILURE 0

#include "client_handler.h"
#include "user.h"

int dbAuth(CLIENT);
void dbGetUser(ClientList *, char *);
int dbValidate(char *);

#endif // __DB__