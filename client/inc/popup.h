#ifndef __POPUP__
#define __POPUP__

#define SUCCESS_POPUP 1
#define ERROR_POPUP 2
#define ALERT_POPUP 3


#include <ncurses.h>

/**
 * @brief 
 * 
 */
void popup(const char *, int);
/**
 * @brief checks the connection status 
 * 
 * if status is successful then successful connection to the entered ip and port is displayed.
 * if status is .. then couldn't find thte connection is displayed.
 */
void connectionStatus(int);



#endif // __POPUP__