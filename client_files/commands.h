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

    char *user_name;
    if (strcmp(data->message, "/help") == 0)
    {
        printf("Command List:\n");
        printf("/whoami -> Displays your name");
        printf("/clear -> To clear screen");
        printf("/dev -> To display creators' names");
    }

    else if (strcmp(data->message, "/whoami") == 0)
    {
        printf("You are \"%s\".\n", data->name);
    }
    else if (strcmp(data->message, "/rickroll") == 0)
    {
        sprintf(data->message, "\r %s RickRolled You: Never Gonna Give you Up.", data->name);
        send(data->sockfd, data->message, sizeof(data->message), 0);
    }
    else if (strcmp(data->message, "/clear") == 0)
    {
        system("clear"); // for windows -> cls , cls;
    }

    else if (strcmp(data->message, "/dev") == 0)
    {
        printf("\r Developers' Name:\n\tGaurav Giri\n\tAnup Bhattarai\n\tKeshab Kamal\n\tAakash Budhathoki\n");
    }

    else if (strcmp(data->message, "/online") == 0)
    {
        send(data->sockfd, data->message, sizeof(data->message), 0);
    }
    else if (strcmp(data->message, "/role") == 0)
    {
        send(data->sockfd, data->message, sizeof(data->message), 0);
    }
    else if (strcmp(user_name = strtok(data->message, " "), "/kick") == 0)
    {
        data->message[5] = ' ';
        send(data->sockfd,data->message,sizeof(data->message),0);
    }
    else
    {
        printf("\rUnknown Command. Use '/help' to show commands.\n");
    }
}

#endif