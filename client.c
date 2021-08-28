#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h> // <winsock2.h> <windows.h>
#include <pthread.h>
#include "client_files/str.h"
#include "client_files/commands.h"

// Global variables
volatile sig_atomic_t flag = 0;
int sockfd = 0;
char name[31] = {};
char password[20] = {};
int opt;
char loginOrRegister[101] = {};
info *data;

void catch_ctrl_c_and_exit(int sig)
{
    flag = 1;
}

void recv_msg_handler()
{
    char receiveMessage[201] = {};
    while (1)
    {
        int receive = recv(sockfd, receiveMessage, 201, 0);
        if (receive > 0)
        {
            printf("\r%s\n", receiveMessage);
            str_overwrite_stdout();
        }
        else if (receive == 0)
        {
            break;
        }
        else
        {
            // -1
        }
    }
}

void send_msg_handler()
{
    char message[101] = {};
    while (1)
    {
        str_overwrite_stdout();
        while (fgets(message, 101, stdin) != NULL)
        {
            str_trim_lf(message, 101);
            if (strlen(message) == 0)
            {
                str_overwrite_stdout();
            }
            else
            {
                break;
            }
        }

        if (strcmp(message, "/exit") == 0)
        {
            break;
        }
        else if (strcmp(message, "/online") == 0)
        {
            send(sockfd, message, sizeof(message), 0);
        }
        else if (message[0] == '/') // commands
        {
            strcpy(data->message, message);
            command(data);
        }
        else
        {
            send(sockfd, message, 101, 0);
        }
    }
    catch_ctrl_c_and_exit(2);
}

int main()
{
    signal(SIGINT, catch_ctrl_c_and_exit);
    short port;
    int leave_flag = 0;
    
    //WSDATA Data
    //WSStartup(MAKEWORD(2,2),&DATA);

    

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Fail to create a socket.");
        exit(EXIT_FAILURE);
    }

    // Socket information
    struct sockaddr_in server_info, client_info;
    int s_addrlen = sizeof(server_info);
    int c_addrlen = sizeof(client_info);
    memset(&server_info, 0, s_addrlen);
    memset(&client_info, 0, c_addrlen);
    server_info.sin_family = PF_INET;
    server_info.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_info.sin_port = htons(8888);

    // Connect to Server
    int err = connect(sockfd, (struct sockaddr *)&server_info, s_addrlen);
    if (err == -1)
    {
        printf("Connection to Server error!\n");
        exit(EXIT_FAILURE);
    }

    // Names
    getsockname(sockfd, (struct sockaddr *)&client_info, (socklen_t *)&c_addrlen);
    getpeername(sockfd, (struct sockaddr *)&server_info, (socklen_t *)&s_addrlen);
    printf("Connect to Server: %s:%d\n", inet_ntoa(server_info.sin_addr), ntohs(server_info.sin_port));
    printf("You are: %s:%d\n\n", inet_ntoa(client_info.sin_addr), ntohs(client_info.sin_port));

    //Login or Register:
    printf("Welcome To ChatChamber:\n1)Login\n2)Register\n");
    printf("You: ");
    scanf("%d", &opt);
    switch (opt)
    {
    case 1:
        printf("\tLogin\nUsername: ");
        if (scanf("%s", name))
        {
            fflush(stdin);
            str_trim_lf(name, 31);
        }
        if (strlen(name) < 2 || strlen(name) >= 30)
        {
            printf("\nName must be more than one and less than thirty characters.\n");
            exit(EXIT_FAILURE);
        }
        printf("\nPassword: ");
        if (scanf("%s", password))
        {
            fflush(stdin);
            str_trim_lf(password, 20);
        }
        if (strlen(password) < 2 || strlen(password) >= 19)
        {
            printf("\nPassword must be more than one and less than twenty characters.\n");
            exit(EXIT_FAILURE);
        }
        sprintf(loginOrRegister,"1 %s %s",name,password);
        break;
    case 2:
         printf("\tRegister\nUsername: ");
        if (scanf("%s", name))
        {
            fflush(stdin);
            str_trim_lf(name, 31);
        }
        if (strlen(name) < 2 || strlen(name) >= 30)
        {
            printf("\nName must be more than one and less than thirty characters.\n");
            exit(EXIT_FAILURE);
        }
        printf("\nPassword: ");
        if (scanf("%s", password))
        {
            fflush(stdin);
            str_trim_lf(password, 20);
        }
        if (strlen(password) < 2 || strlen(password) >= 19)
        {
            printf("\nPassword must be more than one and less than twenty characters.\n");
            exit(EXIT_FAILURE);
        }
        sprintf(loginOrRegister,"2 %s %s",name,password);
        break;

    default:
        printf("\nOut of Option");
        exit(EXIT_FAILURE);
        leave_flag = 1;
        break;
    }
    if (leave_flag == 0){
    send(sockfd, loginOrRegister, sizeof(loginOrRegister), 0); //sent the info about login or registration

    //storing info for data
    data = (info *)malloc(sizeof(info));

    strcpy(data->name, name);
    data->sockfd = sockfd;

    pthread_t send_msg_thread;
    if (pthread_create(&send_msg_thread, NULL, (void *)send_msg_handler, NULL) != 0)
    {
        printf("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }

    pthread_t recv_msg_thread;
    if (pthread_create(&recv_msg_thread, NULL, (void *)recv_msg_handler, NULL) != 0)
    {
        printf("Create pthread error!\n");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        if (flag)
        {
            printf("\nBye\n");
            break;
        }
    }

    close(sockfd);
    }
    return 0;
}
