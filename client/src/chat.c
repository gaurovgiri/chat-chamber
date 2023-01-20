#include <ncurses.h>
#include <string.h>
#include <sys/socket.h>
#include "chat.h"
#include "ui.h"
#include "client.h"
#include "messages.h"
#include "ssl.h"

WINDOW *messageWin;

void recv_msg_handler()
{
    Message receivedMessage;
    int recvStatus;
    messageWin = createMessageBox();
    while (!leaveFlag)
    {
        // curs_set(0);
        memset(&receivedMessage, 0, sizeof(receivedMessage));
        recvStatus = SSL_read(ssl, &receivedMessage, sizeof(Message));

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

    sendMessage.flag = JOIN;

    SSL_write(ssl, &sendMessage, sizeof(Message));

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
        while (!leaveFlag)
        {
            ch = mvwgetch(inputWin, 1, 1 + i);
            if (ch == '\n' && i > 0)
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
            else if (i >= sizeof(sendMessage.msg))
            {
                beep();
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

        if (strncmp(sendMessage.msg, "/exit", sizeof("/exit")) == 0)
        {
            leaveFlag = 1;
            break;
        }
        else
        {
            sendMessage.flag = MSG;
            SSL_write(ssl, &sendMessage, sizeof(sendMessage));
            
        }
    }
    deleteWin(inputWin);
    noecho();
}