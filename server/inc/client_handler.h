#ifndef __CLIENT_HANDLER__
#define __CLIENT_HANDLER__

#define LOGIN 0
#define REGISTER 1
#define _EXIT 2

#include "list.h"
#include "user.h"

typedef struct 
{
    char username[20];
    char password[20];

} CLIENT;

extern User *user;


void *c_handler(void *);
void sendAll(ClientList *, char *);
void closeSocket(ClientList *);
void loginOrReg(ClientList *);
void authLogin(ClientList *);
void authRegister(ClientList *);



#endif // __CLIENT_HANDLER__

