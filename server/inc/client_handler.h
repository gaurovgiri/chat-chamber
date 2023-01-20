#ifndef __CLIENT_HANDLER__
#define __CLIENT_HANDLER__

#define LOGIN 0
#define REGISTER 1
#define _EXIT 2

#include "list.h"
#include "message.h"

typedef struct 
{
    char username[20];
    char password[20];

} CLIENT;



/**
 * @brief handler function assigned to threads upon new connections;
 * 
 * @param [void *] void pointer to accept a ClientList Node
 * 
 */
void *c_handler(void *);



/**
 * @brief closes a socket connection with the client
 * 
 * @param [client] pointer of ClientList node
 * 
 */
void closeSocket(ClientList *);



/**
 * @brief handles login and registration events
 * 
 * @param [client] pointer of ClientList node with client information
 */
void loginOrReg(ClientList *);

/**
 * @brief handles login authentication
 * 
 * @param [client] pointer of ClientList node with client information
 * 
 */
void authLogin(ClientList *);


/**
 * @brief handles registration authentication
 * 
 * @param [client] pointer of ClientList node with client information
 */
void authRegister(ClientList *);



#endif // __CLIENT_HANDLER__
