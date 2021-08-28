#ifndef Client
#define Client
#include "list.h"

void sendAll(ClientList *, char *);

void catch_ctrl_c_and_exit(int sig)
{
    ClientList *tmp;
    char alert[] = "Server is Closed!";
    while (head != NULL)
    {
        printf("\nClose socketfd: %d\n", head->socket);
        sendAll(head, alert);
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
        if (client->socket != tmp->socket && tmp->leave_flag == 0)
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
    memset(msg, 0, sizeof(msg));
    int i, count = 1;
    ClientList *tmp = (ClientList *)head->next;
    msg[0] = '\r';
    while (tmp != NULL)
    {
        for (i = 0; i < strlen(tmp->name); i++)
        {
            msg[count++] = tmp->name[i];
        }
        msg[count++] = ' ';
        msg[count++] = '[';
        for (i = 0; i < strlen(tmp->role); i++)
        {
            msg[count++] = tmp->role[i];
        }
        msg[count++] = ']';
        msg[count++] = '\n';
        tmp = tmp->next;
    }
    send(client->socket, msg, sizeof(msg), 0);
}

void kick(char username[], ClientList *user)
{
    char msg[201];
    ClientList *tmp = (ClientList *)head->next;
    if (strcmp(user->name, username) == 0)
    {
        strcpy(msg, "[You cannot kick yourself.]");
        send(user->socket, msg, sizeof(msg), 0);
        return;
    }
    else if (strcmp(user->role, "admin") == 0)
    {
        sprintf(msg, "You have been kicked by %s", user->name);
        while (tmp != NULL)
        {
            if (strcmp(tmp->name, username) == 0)
            {
                send(tmp->socket, msg, sizeof(msg), 0);
                tmp->leave_flag = 1;
                break;
            }
            else
                tmp = tmp->next;
        }
        sprintf(msg, "%s have been kicked by %s", username, user->name);
        sendAll(tmp, msg);
    }
    else
    {
        strcpy(msg, "You donot have the permission to kick out. Please ask admin.");
        send(user->socket, msg, sizeof(msg), 0);
    }
}

void *c_handler(void *client_t)
{
    ClientList *client = (ClientList *)client_t;
    char chat_name[31] = {};
    // char password[31] = {};
    char recv_msg[101] = {};
    char send_msg[201] = {};
    int data, command_flag = 0;
    char *user_name;
    char args_commands[50];

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
            client->leave_flag = 1;
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
    while (client->leave_flag == 0)
    {
        if (client->leave_flag == 0)
            data = recv(client->socket, recv_msg, sizeof(recv_msg), 0);
        else
            break;
        if (client->leave_flag == 1) //double checking for kicked users
            break;
        if (data > 0)
        {
            strcpy(args_commands, recv_msg);
            if (strlen(recv_msg) == 0)
                continue;
            else if (strcmp(recv_msg, "/online") == 0)
            {
                online(client);
                command_flag = 1;
            }
            else if (strcmp(recv_msg, "/role") == 0)
            {
                sprintf(send_msg, "You are \"%s\"", client->role);
                send(client->socket, send_msg, sizeof(send_msg), 0);
                command_flag = 1;
            }
            else if (strcmp(user_name = strtok(args_commands, " "), "/kick") == 0)
            {
                command_flag = 1;
                if (user_name != NULL)
                {
                    user_name = strtok(NULL, " ");
                    kick(user_name, client);
                }
            }
            else
                sprintf(send_msg, "%s: %s", client->name, recv_msg);
        }
        else if (data == 0 || strcmp(recv_msg, "exit") == 0)
        {
            printf("%s->(%s)(%d) left the chatroom\n", client->name, client->ip, client->socket);
            sprintf(send_msg, "%s left the chatroom", client->name);
            sendAll(client, send_msg);
            client->leave_flag = 1;
        }
        else
        {
            printf("Something Occured Wrong!\n");
            client->leave_flag = 1;
        }
        if (client->leave_flag == 0)
            printf("%s(%s): %s\n", client->name, client->ip, recv_msg);

        if (command_flag == 0 && client->leave_flag != 1)
            sendAll(client, send_msg);
        else
            command_flag = 0;
    }

    // if leaves, truncate the client from the list

    shutdown(client->socket, SHUT_RDWR);
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

        if (head->next == curr)
        {
            strcpy(curr->role, "admin");
            strcpy(send_msg, "Sever made you the admin!!");
            send(curr->socket, send_msg, sizeof(send_msg), 0);
        }
    }
    free(client);
}

#endif