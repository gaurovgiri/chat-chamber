#include "client_handler.h"
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <message.h>
#include "db.h"
#include "ssl.h"

void *c_handler(void *client_t)
{

    ClientList *client = (ClientList *)client_t;

    if (SSL_accept(client->ssl) == FAIL)
        ERR_print_errors_fp(stderr);

    else
    {
        do
        {
            loginOrReg(client);
        } while (!client->authenticated && !client->leave_flag);

        Message message;

        while (!client->leave_flag)
        {
            memset(&message, 0, sizeof(message));
            SSL_read(client->ssl, &message, sizeof(message));

            strncpy(message.sender, client->username, sizeof(client->username));

            switch (message.flag)
            {
            case MSG:
                sendAll(client, message);
                break;

            case JOIN:
                sendAll(client, message);
                break;

            case LEAVE:
                client->leave_flag = 1;
                strncpy(message.msg, "", 0);
                sendAll(client, message);
                break;

            case CMD:
                break;
            default:
                break;
            }
        }
    }
    printf("Closing Connection with socket: %d\n",client->socket);
    closeSocket(client);
}

void loginOrReg(ClientList *client)
{
    int choice;
    SSL_read(client->ssl, &choice, sizeof(int)); // 1
    switch (choice)
    {
    case LOGIN:
        authLogin(client);
        break;
    case REGISTER:
        authRegister(client);
        break;

    case _EXIT:
        client->leave_flag = 1;
        break;

    default:
        break;
    }

    return;
}

void authLogin(ClientList *client)
{
    CLIENT info;
    memset(&info, 0, sizeof(info));
    SSL_read(client->ssl, &info, sizeof(CLIENT));
    printf("%s %s\n", info.username, info.password);
    client->authenticated = loginUser(info);
    SSL_write(client->ssl, &(client->authenticated), sizeof(int));
    if (client->authenticated)
    {
        dbGetUser(client, info.username);
        printf("%s joined the chat\n", client->username); // TODO: send to server with join flag
    }
}

void authRegister(ClientList *client)
{
    char invitationCode[20];
    memset(invitationCode, 0, sizeof(invitationCode));

    SSL_read(client->ssl, invitationCode, sizeof(invitationCode));
    int validCode = dbValidate(invitationCode);
    SSL_write(client->ssl, &validCode, sizeof(int));

    CLIENT info;

    int error = 0;
    if (!validCode)
        return;
    else
    {
        SSL_read(client->ssl, &error, sizeof(int));
        if (error)
            client->authenticated = 0;
        else
        {
            SSL_read(client->ssl, &info, sizeof(CLIENT));
            int created = createUser(info);
            SSL_write(client->ssl, &created, sizeof(int));
            if (!created)
            {
                client->authenticated = 0;
                return;
            }
            else
            {
                client->authenticated = 1;
            }
        }
    }
    if (client->authenticated)
    {
        dbGetUser(client, info.username);
    }
}

void closeSocket(ClientList *client)
{
    SSL_free(client->ssl);
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