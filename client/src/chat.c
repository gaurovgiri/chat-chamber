#include "chat.h"
#include "ui.h"
#include "client.h"
#include <ncurses.h>
#include <string.h>
#include <sys/socket.h>

WINDOW *messageWin;
void recv_msg_handler()
{
    char receivedMessage[101];
    int recvStatus;
    messageWin = createMessageBox();
    while (1)
    {
        // curs_set(0);
        memset(receivedMessage, 0, sizeof(receivedMessage));
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
    keypad(inputWin,TRUE);
    int i,ch;
    // WINDOW *messageWin = createMessageBox();
    noecho();
    curs_set(1);
    while (1)
    {
        memset(sendMessage, 0, sizeof(sendMessage));
        box(inputWin, 0, 0);
        wrefresh(inputWin);
        i = 0;
        while (true)
        {
            ch = mvwgetch(inputWin, 1, 1 + i);
            if (ch == '\n' || i >= sizeof(sendMessage))
            {
                break;
            }
            else if (ch == KEY_BACKSPACE || ch == 127)
            {
                if (i > 0)
                {
                    i--;
                    mvwaddch(inputWin, 1, 1 + i, ' ');
                    wmove(inputWin, 1, 1 + i);
                    wrefresh(inputWin);
                }
            }
            else if (ch == KEY_RESIZE)
            {
                resizeMsg(messageWin);
                resizeInp(inputWin);
            }
            else
            {
                sendMessage[i] = (char)ch;
                mvwaddch(inputWin,1,1+i,(char)ch);
                i++;
                wrefresh(inputWin);
            }
        }
        werase(inputWin);
        wrefresh(inputWin);
        if (strcmp(sendMessage, "/exit") == 0)
        {
            leaveFlag = 1;
            send(sockfd, sendMessage, sizeof(sendMessage), 0);
            break;
        }
        else
        {
            // displayOn(messageWin,sendMessage);
            send(sockfd, sendMessage, sizeof(sendMessage), 0);
        }
    }
    keypad(inputWin,FALSE);
    delwin(inputWin);
    noecho();
}