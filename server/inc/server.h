#ifndef __SERVER__
#define __SERVER__

#include <arpa/inet.h>

extern int s_sockfd,c_sockfd;
extern struct sockaddr_in server_info , client_info;


int startServer(short);
void catch_ctrl_c_and_exit(int);
void cleanup();

#endif //__SERVER__