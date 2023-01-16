#ifndef __USER__
#define __USER__

#define ADMIN 100
#define MEMBER 50


typedef struct
{
    int id;
    char username[20];
    int role;

}User;

#endif // __USER__