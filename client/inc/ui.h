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

void resizeMsg(WINDOW *);
void resizeInp(WINDOW *);

void resize_handler(int);

#endif // __UI__