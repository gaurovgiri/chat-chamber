#include "chat.h"
#include "ui.h"
#include "client.h"
#include <ncurses.h>
#include <string.h>
#include <sys/socket.h>

WINDOW *messageWin;

void recv_msg_handler()
{
    char receivedMessage[101] = {};
    int recvStatus;
    messageWin = createMessageBox();
    while (1)
    {
        recvStatus = recv(sockfd, receivedMessage, 101, 0);

        if (recvStatus > 0)
        {
            displayOn(messageWin, receivedMessage);
        }
    }
    delwin(messageWin);
}

void send_msg_handler()
{
    char sendMessage[101];
    WINDOW *inputWin = createInputBox();
    // WINDOW *messageWin = createMessageBox();
    curs_set(1);
    echo();
    while (1)
    {
        memset(sendMessage,0,sizeof(sendMessage));
        box(inputWin,0,0);
        mvwgetstr(inputWin,1,1,sendMessage);
        wclear(inputWin);
        if (strcmp(sendMessage, "/exit") == 0)
        {
            leaveFlag = 1;
            break;
        }
        else
        {
            // displayOn(messageWin,sendMessage);
            send(sockfd,sendMessage,sizeof(sendMessage),0);
        }
    }
    delwin(inputWin);
    noecho();
}