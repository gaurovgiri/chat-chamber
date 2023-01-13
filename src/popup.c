#include "popup.h"
#include <string.h>

void popup(const char *msg, int code)
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    WINDOW *popup_win = newwin(5, cols - 4, rows / 2 - 3, 2);
    box(popup_win,0,0);
    mvwprintw(popup_win, 2, (cols-4-strlen(msg))/2, msg);
    wrefresh(popup_win);
    getch();
    delwin(popup_win);

}