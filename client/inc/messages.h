#ifndef __MESSAGE__
#define __MESSAGE__

#define MSG 0
#define CMD 1
#define JOIN 2
#define LEAVE 3
#define STOP 4

/**
 * @brief creates a new structure that holds flag , message and sender username.
 * 
 */
typedef struct msg
{
    int flag;
    char sender[20];
    char msg[101];
} Message;

#endif