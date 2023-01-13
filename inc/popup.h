#ifndef __POPUP__
#define __POPUP__

#define SUCCESS_POPUP 1
#define ERROR_POPUP 2
#define ALERT_POPUP 3


#include <ncurses.h>


void popup(const char *, int);
void connectionStatus(int);



#endif // __POPUP__