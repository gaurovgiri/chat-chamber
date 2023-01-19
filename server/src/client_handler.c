#include "client_handler.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <message.h>

void *c_handler(void *client_t)
{

    ClientList *client = (ClientList *)client_t;

    do
    {
        client->authenticated = 0;
        loginOrReg(client);
    } while (!client->authenticated);

    Message message;

    while (!client->leave_flag)
    {
        memset(&message, 0, sizeof(message));
        recv(client->socket, &message, sizeof(message), 0);
        sendAll(client,message.msg);
    }
    closeSocket(client);
}

void loginOrReg(ClientList *client)
{
    int choice;
    recv(client->socket, &choice, sizeof(int), 0); // 1
    switch (choice)
    {
    case LOGIN:
        authLogin(client);
        break;
    case REGISTER:
        authRegister(client);
        break;

    case _EXIT:
        closeSocket(client);
        break;

    default:
        break;
    }

    return;
}

void authLogin(ClientList *client)
{
    CLIENT info;
    recv(client->socket, &info, sizeof(CLIENT), 0);
    int authenticated = dbAuth(info);
    client->authenticated = authenticated;
    send(client->socket, &authenticated, sizeof(int), 0);
    if (client->authenticated)
    {
        dbGetUser(client, info.name);
        printf("%s joined the chat\n",client->username);
    }
}

void authRegister(ClientList *client)
{
    char invitationCode[20];
    memset(invitationCode, 0, sizeof(invitationCode));

    recv(client->socket, invitationCode, sizeof(invitationCode), 0);
    int validCode = dbValidate(invitationCode);
    send(client->socket, &validCode, sizeof(int), 0);

    CLIENT info;

    int error = 0;
    if (!validCode)
        return;
    else
    {
        recv(client->socket, &error, sizeof(int), 0);
        if (error)
            client->authenticated = 0;
        else
        {
            recv(client->socket, &info, sizeof(CLIENT), 0);
            int userExist = dbAuth(info);
            send(client->socket, &userExist, sizeof(int), 0);
            if (userExist)
            {
                client->authenticated = 0;
                return;
            }
            else
            {
                client->authenticated = 1;
                // dbStore;
            }
        }
    }
    if (client->authenticated)
    {
        dbGetUser(client, info.name);
    }
}

void closeSocket(ClientList *client)
{
    close(client->socket);
    if (client == curr)
    {
        curr = client->prev;
        curr->next = NULL;
    }
    else
    {
        client->prev->next = client->next;
        client->next->prev = client->prev;
    }
    free(client);
}