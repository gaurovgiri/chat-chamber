#ifndef __UI__
#define __UI__

#define LOGIN 0
#define REGISTER 1
#define _EXIT 2

#include <ncurses.h>
#include <messages.h>

int menu(char *[], int);
void loginOrReg();

/**
 * @brief login page after the login window is prompted
 * 
 * input username and password
 * 
 * \param [none]
 * 
 */
void loginPage();
/**
 * @brief prompts the window for registration
 * 
 * displays a message box for the user to enter a new usernmae to register.
 * enter the password , confirm the password and enter a valid server invitaion code .
 * 
 * \param [none]
 * 
 */
void registerPage();

/**
 * @brief Create a Message Box object
 * 
 * @return WINDOW* 
 */
WINDOW *createMessageBox();
/**
 * @brief Create a Input Box object
 * 
 * @return WINDOW* 
 */
WINDOW *createInputBox();

/**
 * @brief creates a display
 * 
 * \param [screen] pointer to n curses window . 
 * \param [msg] a message  
 * 
 */
void displayOn(WINDOW *, Message);

/**
 * @brief deletes a created screen
 * 
 * \param [*screen] points to the screen that needs to be deleted.
 * 
 */
void deleteWin(WINDOW *);

void resizeMsg(WINDOW *);

/**
 * @brief resizes the prompted with the size as input from the user 
 * 
 * \param [*screen] points to the window that is to be resized.
 * 
 */
void resizeInp(WINDOW *);

#endif // __UI__