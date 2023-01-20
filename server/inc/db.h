#ifndef __DB__
#define __DB__

#define AUTH_SUCCESS 1
#define AUTH_FAILURE 0

#include "client_handler.h"
#include <sqlite3.h>

extern sqlite3 *db;

/**
 * @brief callback function for sqlite connection
 *
 * @param [NotUsed, argc, argv, azcolname] standard function parameters for callback function
 *
 * @return int
 */
static int callback(void *, int, char **, char **);

/**
 * @brief initalize Database
 *  if no database found, create database.
 *
 * 
 * 
 */
void initDB();

/**
 * @brief Create a User object
 *  
 * if user is created returns AUTH_SUCCESS
 * else returns AUTH_FAILED
 *   
 * @param [info] object that stores client credentials for registration
 * 
 * @return int 
 */
int createUser(CLIENT);

/**
 * @brief authenticates users upon login
 * 
 * if authenticated returns AUTH_SUCESS
 * else AUTH_FAILED
 * 
 * @param [info] object that stores client credentials for login
 * 
 * 
 *  
 * @return int 
 */
int loginUser(CLIENT);


/**
 * @brief get user data from database; 
 *  
 * @param [info] object that stores client credentials;
 * @param [name] string to check in database 
 */

void dbGetUser(ClientList *, char *);


/**
 * @brief validates the server invitation code
 *  if correct invitation code entered returns AUTH_SUCCESS
 *  else returns AUTH_FAILED 
 * 
 * @param [invitation_code] string to compare and validate invitation code
 * @return int 
 */
int dbValidate(char *);

#endif // __DB__