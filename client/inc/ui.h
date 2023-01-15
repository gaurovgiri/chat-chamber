#ifndef __UI__
#define __UI__

#include <ncurses.h>

int menu(char *[], int);
void loginOrReg();

void loginPage();
void registerPage();

WINDOW *createMessageBox();
WINDOW *createInputBox();

void displayOn(WINDOW *, char *);

void deleteWin(WINDOW *);

#endif // __UI__