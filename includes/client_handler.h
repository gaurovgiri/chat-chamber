#ifndef Client
#define Client
#include "list.h"
#include <string.h>

struct user_data
{
    char username[31];
    char password[31];
    char role[10];
} user_info;

void sendAll(ClientList *, char *);

void catch_ctrl_c_and_exit(int);

void makeAdmin(ClientList *, char);


void online(ClientList *);

void kick(ClientList *, char );
void whispered(ClientList *, char , char);

void *c_handler(void *);

#endif