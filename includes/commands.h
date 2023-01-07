#ifndef COMMAND
#define COMMAND

typedef struct DATA
{
    char name[31];
    int sockfd;
    char message[101];
} info;

void command(info *data); //commands are written here

#endif