#include "client_handler.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>

User *user;

void sendAll(ClientList *client, char *msg)
{
    ClientList *tmp = (ClientList *)head->next;
    while (tmp != NULL)
    {

        printf("Send to socket %d: \"%s\" \n", tmp->socket, msg);
        send(tmp->socket, msg, 101, 0);
        tmp = tmp->next;
    }
}

void *c_handler(void *client_t)
{

    ClientList *client = (ClientList *)client_t;

    do
    {
        client->authenticated = 0;
        loginOrReg(client);
    } while (!client->authenticated);

    char msg[101];

    while (1)
    {
        memset(msg, 0, sizeof(msg));
        recv(client->socket, msg, sizeof(msg), 0);
        if (strcmp(msg, "/exit") == 0)
        {
            break;
        }
        else
        {
            sendAll(client, msg);
        }
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
}

void authRegister(ClientList *client)
{
    char invitationCode[20];
    memset(invitationCode, 0, sizeof(invitationCode));

    recv(client->socket, invitationCode, sizeof(invitationCode), 0);
    int validCode = dbValidate(invitationCode);
    send(client->socket, &validCode, sizeof(int), 0);

    int error = 0;
    if (!validCode)
        return;
    else
    {
        recv(client->socket, &error, sizeof(int), 0);
        if (error)
            client->authenticated = error = 0;
        else
        {
            CLIENT info;
            recv(client->socket, &info, sizeof(CLIENT), 0);
            int userExist = dbAuth(info);
            send(client->socket, &userExist, sizeof(int), 0);
            if (userExist)
            {
                return;
            }
            else
            {
                client->authenticated = 1;
                // dbStore;
            }
        }
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