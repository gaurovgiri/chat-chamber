#include "chat.h"
#include "ui.h"
#include "client.h"
#include "messages.h"
#include <ncurses.h>
#include <string.h>
#include <sys/socket.h>

WINDOW *messageWin;

void recv_msg_handler()
{
    char receivedMessage[123];
    int recvStatus;
    messageWin = createMessageBox();
    while (1)
    {
        // curs_set(0);
        memset(receivedMessage, 0, sizeof(receivedMessage));
        recvStatus = recv(sockfd, receivedMessage, sizeof(receivedMessage), 0);

        if (recvStatus > 0)
        {
            displayOn(messageWin, receivedMessage);
        }
    }
    deleteWin(messageWin);
}

void send_msg_handler()
{
    Message sendMessage;
    WINDOW *inputWin = createInputBox();
    wrefresh(inputWin);
    int i, ch;
    noecho();
    curs_set(1);
    while (1)
    {
        memset(&sendMessage, 0, sizeof(sendMessage));
        box(inputWin, 0, 0);
        wrefresh(inputWin);
        i = 0;
        while (true)
        {
            ch = mvwgetch(inputWin, 1, 1 + i);
            if (ch == '\n' || i >= sizeof(sendMessage.msg))
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
                wrefresh(messageWin);
                wrefresh(inputWin);
            }
            else
            {
                sendMessage.msg[i] = (char)ch;
                mvwaddch(inputWin, 1, 1 + i, (char)ch);
                i++;
                wrefresh(inputWin);
            }
        }
        werase(inputWin);
        wrefresh(inputWin);

        // displayOn(messageWin,sendMessage);
        send(sockfd, &sendMessage, sizeof(sendMessage), 0);
    }
    deleteWin(inputWin);
    noecho();
}