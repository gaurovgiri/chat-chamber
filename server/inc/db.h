#ifndef __DB__
#define __DB__

#define AUTH_SUCCESS  1
#define AUTH_FAILURE  0


#include "client_handler.h"
#include "user.h"
#include <sqlite3.h>


extern sqlite3 *db;

static int callback(void *,int, char **,char **);

void initDB();
int createUser(CLIENT);
int loginUser(CLIENT);
void dbGetUser(ClientList *, char *);
int dbValidate(char *);

#endif // __DB__