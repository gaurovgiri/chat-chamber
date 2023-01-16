#ifndef __UI__
#define __UI__

#define LOGIN 0
#define REGISTER 1
#define _EXIT 2

#include <ncurses.h>


int menu(char *[], int);
void loginOrReg();

void loginPage();
void registerPage();

WINDOW *createMessageBox();
WINDOW *createInputBox();

void displayOn(WINDOW *, char *);

void deleteWin(WINDOW *);

void resizeMsg(WINDOW *);
void resizeInp(WINDOW *);

void resize_handler(int);

#endif // __UI__