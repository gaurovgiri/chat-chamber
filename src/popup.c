#include "popup.h"
#include <string.h>
#include "client.h"
#include "utils.h"
#include <malloc.h>

void popup(const char *msg, int code)
{
    int rows, cols;
    char *status_code;
    status_code = (char *)malloc(sizeof("Code: ")+6);
    snprintf(status_code, sizeof(status_code), "Code: %d", code);
    getmaxyx(stdscr, rows, cols);
    WINDOW *popup_win = newwin(6, cols - 5, rows / 2 - 3, 2);
    box(popup_win, 0, 0);
    mvwprintw(popup_win, 2, (cols - 4 - strlen(msg)) / 2, msg);
    mvwprintw(popup_win, 3, (cols - 4 - strlen(status_code)) / 2, status_code);
    mvwprintw(popup_win,4,(cols-4-strlen("Press any key to continue."))/2,"Press any key to continue.");
    wrefresh(popup_win);
    getch();
    delwin(popup_win);
    refresh();
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

        snprintf(msg, sizeof(msg), "Couldn't Connected to %s:%d", getServerIP(), getServerPort());
        popup(msg, ERROR_POPUP);
    }
}