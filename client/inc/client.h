#ifndef __CLIENT__
#define __CLIENT__

#define EXIT_0 -1   // Code Status for exits without connecting to the server
#define SUCCESS_0 0 // Code Status for successful connection to the server
#include <sys/socket.h>
#include <stdint.h>


extern int sockfd, leaveFlag,connected;
extern struct sockaddr_in server_info, client_info;

/**
 * @brief to catch the signal generated when ctrl+c is pressed.
 * 
 */
void catch_ctrl_c_and_exit(int);
/**
 * @brief prompts the user to input server ip and port and then read the input
 * \param [ip] ip address entered by the user.
 * \param [port] points to the port .
 * 
 */
void serverPrompt(char[], short *);
/**
 * @brief 
 * 
 */
void cleanup();
/**
 * @brief Get the server IP object and server port
 * 
 * \param [server ip] takes server ip as input.
 * \param [server port] takes server port as input.
 * 
 * @return int 
 */
int connectToServer(char[], short);

/**
 * @brief Get the Server I P object
 * 
 * @return char* 
 */
char *getServerIP();
/**
 * @brief Get the Server Port object
 * 
 * @return uint16_t 
 */
uint16_t getServerPort();


/**
 * @brief creates a new structure that holds username and password
 * 
 * this is the username and password entered by the user
 * 
 */
typedef struct
{
    char username[20];
    char password[20];
}CLIENT;

#endif //__CLIENT__