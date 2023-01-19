#include "ui.h"
#include "popup.h"
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>
#include "client.h"

int authenticated = 0, error = 0;
CLIENT info;


int menu(char *options[], int option_len)
{
    WINDOW *menuWin = newwin(stdscr->_maxy, stdscr->_maxx, 0, 0);
    keypad(menuWin, TRUE);
    curs_set(0);
    int index = 0;
    int ch;

    while (true)
    {
        wclear(menuWin);
        for (int i = 0; i < option_len; i++)
        {
            if (i == index)
            {
                wattron(menuWin, A_REVERSE);

                wprintw(menuWin, "%d. %s\n", i + 1, options[i]);
                wattroff(menuWin, A_REVERSE);
            }
            else
            {
                wprintw(menuWin, "%d. %s\n", i + 1, options[i]);
            }
        }

        wrefresh(menuWin);

        ch = wgetch(menuWin);

        switch (ch)
        {
        case KEY_DOWN:
            index++;
            if (index >= option_len)
                index = 0;
            break;
        case KEY_UP:
            index--;
            if (index < 0)
                index = option_len - 1;
            break;
        case '\n':
            goto END;
        case KEY_ENTER:
            goto END;
        case 'q':
            exit(KEY_EXIT);
        default:
            break;
        }
    }
END:
    keypad(menuWin, false);
    deleteWin(menuWin);
    return index;
}

void loginOrReg()
{
    char *options[3] = {"Login", "Register", "Exit"};
    int choice;

    do
    {
        choice = menu(options, 3);

        send(sockfd, &choice, sizeof(int), 0); // 1
        switch (choice)
        {
        case LOGIN:
            loginPage();
            break;
        case REGISTER:
            registerPage();
            break;
        case _EXIT:
            exit(0);
        default:
            break;
        }

    } while (!authenticated);

    return;
}

void loginPage()
{

    clear();
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    noecho();

    WINDOW *loginBox = newwin(5, cols - 20, rows / 2 - 2, 10);
    box(loginBox, 0, 0);

    mvwprintw(loginBox, 1, cols / 2 - 5, "Login");
    mvwprintw(loginBox, 2, 2, "Username: ");
    mvwprintw(loginBox, 3, 2, "Password: ");

    wrefresh(loginBox);

    memset(info.username, 0, sizeof(info.username));
    memset(info.password, 0, sizeof(info.password));

    echo();
    curs_set(1);
    mvwgetstr(loginBox, 2, 12, info.username);
    noecho();
    int i = 0;
    while (true)
    {
        char ch = mvwgetch(loginBox, 3, 12 + i);

        if (ch == '\n')
        {
            break;
        }
        else if (ch == KEY_BACKSPACE || ch == 127)
        {
            if (i > 0)
            {
                i--;
                mvwaddch(loginBox, 3, 12 + i, ' ');
                wmove(loginBox, 3, 12 + i);
                wrefresh(loginBox);
            }
        }
        else if (i >= sizeof(info.password))
        {
            beep();
        }
        else
        {
            info.password[i] = ch;
            mvwaddch(loginBox, 3, 12 + i, '*');
            i++;
            wrefresh(loginBox);
        }
    }

    send(sockfd, &info, sizeof(CLIENT), 0);

    recv(sockfd, &authenticated, sizeof(int), 0);
    if (!authenticated)
    {
        popup("Authentication Failed!", -1);
    }
    curs_set(0);
    deleteWin(loginBox);
}

void registerPage()
{

    WINDOW *regBox = newwin(10, 40, 5, 5);
    char code[20];
    char username[20], password[20], confirm[20];
    error = 0;

    memset(username, 0, sizeof(username));
    memset(password, 0, sizeof(password));
    memset(confirm, 0, sizeof(confirm));
    memset(code, 0, sizeof(code));

    box(regBox, 0, 0);
    curs_set(1);
    mvwprintw(regBox, 1, 1, "Invitation Code: ");
    wrefresh(regBox);

    echo();

    mvwgetstr(regBox, 1, 18, code);
    send(sockfd, code, sizeof(code), 0);
    int validCode;
    recv(sockfd, &validCode, sizeof(int), 0);

    if (validCode)
    {
        mvwprintw(regBox, 3, 1, "Username: ");
        mvwprintw(regBox, 4, 1, "Password: ");
        mvwprintw(regBox, 5, 1, "Confirm Password: ");
        wrefresh(regBox);

        // username
        strncpy(username, "", sizeof(username));
        mvwgetstr(regBox, 3, 11, username);

        // password
        strncpy(password, "", sizeof(password));
        strncpy(confirm, "", sizeof(confirm));
        noecho();
        int i = 0;
        while (true)
        {
            char ch = mvwgetch(regBox, 4, 11 + i);

            if (ch == '\n')
            {
                break;
            }
            else if (ch == KEY_BACKSPACE || ch == 127)
            {
                if (i > 0)
                {
                    i--;
                    mvwaddch(regBox, 4, 11 + i, ' ');
                    wmove(regBox, 4, 11 + i);
                    wrefresh(regBox);
                }
            }
            else
            {
                password[i] = ch;
                mvwaddch(regBox, 4, 11 + i, '*');
                i++;
                wrefresh(regBox);
            }
        }

        // confirm password
        i = 0;
        while (true)
        {
            char ch = mvwgetch(regBox, 5, 19 + i);

            if (ch == '\n')
            {
                break;
            }
            else if (ch == KEY_BACKSPACE || ch == 127)
            {
                if (i > 0)
                {
                    i--;
                    mvwaddch(regBox, 5, 19 + i, ' ');
                    wmove(regBox, 5, 19 + i);
                    wrefresh(regBox);
                }
            }
            else
            {
                confirm[i] = ch;
                mvwaddch(regBox, 5, 19 + i, '*');
                i++;
                wrefresh(regBox);
            }
        }

        if (strcmp(password, confirm) != 0)
        {
            error = 1;
            popup("Password didn't match", 2);
        }
    }
    else
    {
        error = 1;
        popup("Bad Invitation Code", -1);
        return;
    }
    send(sockfd, &error, sizeof(int), 0);
    if (error)
    {
        error = 0;
    }
    else
    {
        int created;
        memset(&info, 0, sizeof(info));
        strcpy(info.username, username);
        strcpy(info.password, password);
        send(sockfd, &info, sizeof(CLIENT), 0);
        recv(sockfd, &created, sizeof(int), 0);
        if (!created)
        {
            popup("Username already exists!", -1);
        }
        else
        {
            authenticated = created;
        }
    }
    curs_set(0);
    deleteWin(regBox);
}

WINDOW *createMessageBox()
{

    int rows, cols;
    getmaxyx(stdscr, rows, cols);                      // Get the maximum screen dimensions
    WINDOW *messageWin = newwin(rows - 5, cols, 0, 0); // Create a new window for the messages
    scrollok(messageWin, TRUE);                        // Allow scrolling in the messages window

    werase(stdscr);
    refresh();

    werase(messageWin);
    wrefresh(messageWin); // Refresh the messages window
    return messageWin;
}

WINDOW *createInputBox()
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    WINDOW *inputWin = newwin(3, cols, rows - 4, 0);
    box(inputWin, 0, 0);

    werase(stdscr);
    refresh();
    werase(inputWin);
    wrefresh(inputWin);
    return inputWin;
}

void displayOn(WINDOW *screen, char *msg)
{
    wprintw(screen, "%s\n", msg);
    wrefresh(screen);
}

void deleteWin(WINDOW *screen)
{
    werase(screen);
    wrefresh(screen);
    delwin(screen);
    refresh();
}

void resizeMsg(WINDOW *screen)
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    wresize(screen, rows - 5, cols);
    mvwin(screen, 0, 0);
    wrefresh(screen);
}

void resizeInp(WINDOW *screen)
{
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    wresize(screen, 3, cols);
    mvwin(screen, rows - 4, 0);
    wrefresh(screen);
}