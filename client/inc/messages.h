#ifndef __MESSAGE__
#define __MESSAGE__

#define MSG 0
#define CMD 1
#define LEAVE 2

typedef struct msg
{
    int flag;
    char msg[101];
} Message;

#endif