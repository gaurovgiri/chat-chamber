#include "ui.h"
#include "popup.h"
#include <string.h>
#include <ncurses.h>
#include <stdlib.h>

int menu(char *options[], int option_len)
{
    keypad(stdscr, TRUE);
    curs_set(0);
    int index = 0;
    int ch;

    while (true)
    {
        clear();
        for (int i = 0; i < option_len; i++)
        {
            if (i == index)
            {
                attron(A_REVERSE);
                printw("%d. %s\n", i + 1, options[i]);
                attroff(A_REVERSE);
            }
            else
            {
                printw("%d. %s\n", i + 1, options[i]);
            }
        }

        refresh();

        ch = getch();

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
    keypad(stdscr, false);
    return index;
}

void loginOrReg()
{
    char *options[3] = {"Login", "Register", "Exit"};
    int choice = menu(options, 3);

    switch (choice)
    {
    case 0:
        loginPage();
        break;
    case 1:
        registerPage();
        break;
    case 2:
        exit(0);
        break;
    default:
        break;
    }

    exit(0);
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

    char username[20];
    char password[20];
    echo();
    curs_set(1);
    mvwgetstr(loginBox, 2, 12, username);
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
        else
        {
            password[i] = ch;
            mvwaddch(loginBox, 3, 12 + i, '*');
            i++;
            wrefresh(loginBox);
        }
    }
    curs_set(0);
    delwin(loginBox);
    getch();
}

void registerPage()
{

    WINDOW *regBox = newwin(10, 40, 5, 5);
    box(regBox, 0, 0);
    curs_set(1);
    mvwprintw(regBox, 1, 1, "Invitation Code: ");
    wrefresh(regBox);

    char code[20];
    char username[20], password[20], confirm[20];
    mvwgetstr(regBox, 1, 18, code);

    if (strcmp(code, "correct_code") == 0)
    {
        mvwprintw(regBox, 3, 1, "Username: ");
        mvwprintw(regBox, 4, 1, "Password: ");
        mvwprintw(regBox, 5, 1, "Confirm Password: ");
        wrefresh(regBox);

        // username
        strncpy(username,"",sizeof(username));
        mvwgetstr(regBox, 3, 11, username);

        // password
        strncpy(password,"",sizeof(password));
        strncpy(confirm,"",sizeof(confirm));
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
        if (strcmp(password, confirm) == 0)
        {
            popup("Registered Successfully", 1);
        }
        else
        {
            popup("Password didn't match", 2);
            delwin(regBox);
            loginOrReg();
        }
    }
    else
    {
        popup("Bad Invitation Code", -1);
        delwin(regBox);
        loginOrReg();
    }
    curs_set(0);
    delwin(regBox);
}