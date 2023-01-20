#ifndef __CLIENT__
#define __CLIENT__

#define EXIT_0 -1   // Code Status for exits without connecting to the server
#define SUCCESS_0 0 // Code Status for successful connection to the server
#include <sys/socket.h>


extern int sockfd, leaveFlag,connected;
extern struct sockaddr_in server_info, client_info;

void catch_ctrl_c_and_exit(int);
void serverPrompt(char[], short *);
void cleanup();
int connectToServer(char[], short);
char *getServerIP();
uint16_t getServerPort();

typedef struct
{
    char username[20];
    char password[20];
}CLIENT;

#endif //__CLIENT__