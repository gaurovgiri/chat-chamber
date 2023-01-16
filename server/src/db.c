#include "db.h"
#include <string.h>
#include <stdlib.h>

int dbAuth(CLIENT info)
{
    if (strcmp(info.name, "gaurav") == 0)
    {
        return AUTH_SUCCESS;
    }
    else
    {
        return AUTH_FAILURE;
    }
}

void dbGetUser(User *user)
{
    user = (User *)malloc(sizeof(User));
    user->id = 1;
    strcpy(user->username, "Gaurav");
    user->role = ADMIN;
}

int dbValidate(char *invitationCode)
{
    if (strcmp(invitationCode, "correct_code") == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}