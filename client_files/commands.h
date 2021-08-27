#ifndef COMMAND
#define COMMAND

typedef struct DATA
{
    char name[31];
    int sockfd;
    char message[101];
} info;

void command(info *data) //commands are written here
{

    char message[101];
    strcpy(message, data->message + 1); // removing slash

    if (strcmp(message, "help") == 0)
    {
        printf("Command List:\n");
        printf("whoami -> Displays your name");
        printf("clear -> To clear screen");
        printf("dev -> To display creators' names");
    }

    else if (strcmp(message, "whoami") == 0)
    {
        printf("You are \"%s\".\n", data->name);
    }
    else if (strcmp(message, "rickroll") == 0)
    {
        sprintf(message, "\r %s RickRolled You: Never Gonna Give you Up.", data->name);
        send(data->sockfd, message, sizeof(message), 0);
    }
    else if (strcmp(message, "clear") == 0)
    {
        system("clear"); // for windows -> cls , cls;
    }

    else if (strcmp(message, "dev") == 0)
    {
        printf("\r Developers' Name:\n\tGaurav Giri\n\tAnup Bhattarai\n\tKeshab Kamal\n\tAakash Budhathoki\n");
    }
    
    else
    {
        printf("\rUnknown Command. Use '/help' to show commands.\n");
    }
}

#endif