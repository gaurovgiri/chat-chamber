#ifndef Client
#define Client
#include "list.h"

void catch_ctrl_c_and_exit(int sig)
{
    ClientList *tmp;
    while (head != NULL)
    {
        printf("\nClose socketfd: %d\n", head->socket);
        close(head->socket); // close all socket include server_sockfd
        tmp = (ClientList *)head;
        head = head->next;
        free(tmp);
    }
    printf("Bye\n");
    exit(EXIT_SUCCESS);
}

void sendAll(ClientList *client, char *msg)
{
    ClientList *tmp = (ClientList *)head->next;
    while (tmp != NULL)
    {
        if (client->socket != tmp->socket)
        {
            printf("Send to socket %d: \"%s\" \n", tmp->socket, msg);
            send(tmp->socket, msg, 201, 0);
        }
        tmp = tmp->next;
    }
}

void online(ClientList *client)
{
    char msg[201];
    int i, count = 0;
    ClientList *tmp = (ClientList *)head->next;
    while (tmp != NULL)
    {
        for (i = 0; i < strlen(tmp->name); i++)
        {
            msg[count++] = tmp->name[i];
        }
        msg[count++] = '\n';
        tmp = tmp->next;
    }
    send(client->socket, msg, sizeof(msg), 0);
}

void *c_handler(void *client_t)
{
    ClientList *client = (ClientList *)client_t;
    char chat_name[31] = {};
    // char password[31] = {};
    char recv_msg[101] = {};
    char send_msg[201] = {};
    int leave_flag = 0, data;
    // char opt[4]; // check the option

    //login or register
    // recv(client->socket,opt,sizeof(opt),0);

    switch (2) //atoi(opt)
    {
    case 1: //login

        break;

    case 2: //register
        if (recv(client->socket, chat_name, sizeof(chat_name), 0) <= 0 || strlen(chat_name) < 2 || strlen(chat_name) >= 30)
        {
            printf("%s didn't input a name.", client->ip);
            leave_flag = 1;
        }
        else
        {
            strncpy(client->name, chat_name, sizeof(chat_name));
            printf("%s->(%s)(%d) joined the chatroom\n", client->name, client->ip, client->socket);
            sprintf(send_msg, "%s joined the chatroom", client->name);
            sendAll(client, send_msg);
        }
        break;

    default:
        break;
    }

    //Chat
    while (1)
    {
        if (leave_flag)
            break;

        data = recv(client->socket, recv_msg, sizeof(recv_msg), 0);
        if (data > 0)
        {
            if (strlen(recv_msg) == 0)
                continue;
            else if (strcmp(recv_msg, "/online") == 0)
            {
                online(client);
            }
            else
            sprintf(send_msg, "%s: %s", client->name, recv_msg);
        }
        else if (data == 0 || strcmp(recv_msg, "exit") == 0)
        {
            printf("%s->(%s)(%d) left the chatroom\n", client->name, client->ip, client->socket);
            sprintf(send_msg, "%s left he chatroom", client->name);
            leave_flag = 1;
        }
        else
        {
            printf("Something Occured Wrong!\n");
            leave_flag = 1;
        }

        printf("%s\n", recv_msg);
        sendAll(client, send_msg);
    }

    // if leaves, truncate the client from the list

    close(client->socket);
    if (client == curr)
    {
        client->prev->next = NULL;
        curr = client->prev;
    }
    else
    {
        client->prev->next = client->next;
        client->next->prev = client->prev;
    }
    free(client);
}

#endif