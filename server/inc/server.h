#ifndef __SERVER__
#define __SERVER__

#include <arpa/inet.h>

extern int s_sockfd,c_sockfd;
extern struct sockaddr_in server_info , client_info;


/**
 * @brief starts the server 
 * 
 * \param [port] port of the server
 * 
 * @return int 
 */
int startServer(short);
/**
 * @brief to catch the signal generated when ctrl+c is pressed.
 * 
 */
void catch_ctrl_c_and_exit(int);
/**
 * @brief clears the console
 * 
 */
void cleanup();

#endif //__SERVER__