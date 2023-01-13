#include "popup.h"
#include <string.h>
#include "client.h"


void popup(const char *msg, int code)
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    WINDOW *popup_win = newwin(5, cols - 4, rows / 2 - 3, 2);
    box(popup_win, 0, 0);
    mvwprintw(popup_win, 2, (cols - 4 - strlen(msg)) / 2, msg);
    wrefresh(popup_win);
    getch();
    delwin(popup_win);
}

void connectionStatus(int status)
{
    char msg[100];
    if (status == SUCCESS_0)
    {
        snprintf(msg, sizeof(msg), "Successfully Connected to %s:%d", getServerIP(), getServerPort());
        popup(msg, SUCCESS_POPUP);
    }
    else if (status == EXIT_0)
    {

        snprintf(msg, sizeof(msg), "Couldn't Connected to %s:%d", getServerIP(),getServerPort());
        popup(msg, ERROR_POPUP);
    }
}