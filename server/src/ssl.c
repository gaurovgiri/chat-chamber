#include <unistd.h> /*FOR USING FORK for at a time send and receive messages*/

#include <errno.h>  /*USING THE ERROR LIBRARY FOR FINDING ERRORS*/
#include <malloc.h> /*FOR MEMORY ALLOCATION */

#include <string.h> /*using fgets funtions for geting input from user*/

#include <arpa/inet.h> /*for using ascii to network bit*/

#include <sys/socket.h> /*for creating sockets*/

#include <sys/types.h> /*for using sockets*/

#include <netinet/in.h> /* network to asii bit */

#include <resolv.h> /*server to find out the runner's IP address*/

#include <stdio.h> /*standard i/o*/

#include "ssl.h"

#define FAIL -1 /*for error output == -1 */

#define BUFFER 1024 /*buffer for reading messages*/

int OpenListener(int port)

{
    int sd;
    struct sockaddr_in addr; /*creating the sockets*/
    sd = socket(PF_INET, SOCK_STREAM, 0);
    bzero(&addr, sizeof(addr)); /*free output the garbage space in memory*/

    addr.sin_family = AF_INET;   /*getting ip address form machine */
    addr.sin_port = htons(port); /* converting host bit to n/w bit */
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sd, (struct sockaddr *)&addr, sizeof(addr)) != 0) /* assiging the ip address and port*/

    {

        perror("can't bind port"); /* reporting error using errno.h library */

        abort(); /*if error will be there then abort the process */
    }

    if (listen(sd, 10) != 0) /*for listening to max of 10 clients in the queue*/

    {

        perror("Can't configure listening port"); /* reporting error using errno.h library */

        abort(); /*if erroor will be there then abort the process */
    }

    return sd;
}

int isRoot() /*for checking if the root user is executing the server*/

{

    if (getuid() != 0)

    {

        return 0;
    }

    else

    {

        return 1; /* if root user is not executing report must be user */
    }
}

SSL_CTX *InitServerCTX(void) /*creating and setting up ssl context structure*/

{
    SSL_METHOD *method;

    SSL_CTX *ctx;

    OpenSSL_add_all_algorithms(); /* load & register all cryptos, etc. */

    SSL_load_error_strings(); /* load all error messages */

    method = TLSv1_2_server_method(); /* create new server-method instance */

    ctx = SSL_CTX_new(method); /* create new context from method */

    if (ctx == NULL)

    {

        ERR_print_errors_fp(stderr);

        abort();
    }

    return ctx;
}

void LoadCertificates(SSL_CTX *ctx, char *CertFile, char *KeyFile) /* to load a certificate into an SSL_CTX structure*/

{

    /* set the local certificate from CertFile */

    if (SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0)

    {

        ERR_print_errors_fp(stderr);

        abort();
    }

    /* set the private key from KeyFile (may be the same as CertFile) */

    if (SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0)

    {

        ERR_print_errors_fp(stderr);

        abort();
    }

    /* verify private key */

    if (!SSL_CTX_check_private_key(ctx))

    {

        fprintf(stderr, "Private key does not match the public certificate\n");

        abort();
    }
}

void ShowCerts(SSL *ssl) /*show the ceritficates to client and match them*/

{
    X509 *cert;

    char *line;

    cert = SSL_get_peer_certificate(ssl); /* Get certificates (if available) */

    if (cert != NULL)

    {

        printf("Server certificates:\n");

        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);

        printf("Server: %s\n", line); /*server certifcates*/

        free(line);

        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);

        printf("client: %s\n", line); /*client certificates*/

        free(line);

        X509_free(cert);
    }

    else

        printf("No certificates.\n");
}

void Servlet(SSL *ssl) /* Serve the connection -- threadable */

{
    char buf[1024];

    int sd, bytes;

    char input[BUFFER];

    pid_t cpid;

    if (SSL_accept(ssl) == FAIL) /* do SSL-protocol accept */

        ERR_print_errors_fp(stderr);

    else

    {

        ShowCerts(ssl); /* get any certificates */

        /*Fork system call is used to create a new process*/

        cpid = fork();

        if (cpid == 0)

        {

            while (1)
            {

                bytes = SSL_read(ssl, buf, sizeof(buf)); /* get request and read message from server*/

                if (bytes > 0)

                {

                    buf[bytes] = 0;

                    printf("\nMESSAGE FROM SERVER:%s\n", buf);
                }

                else

                    ERR_print_errors_fp(stderr);
            }
        }

        else
        {

            while (1)
            {

                printf("\nMESSAGE TO CLIENT:");

                fgets(input, BUFFER, stdin); /* get request and reply to client*/

                SSL_write(ssl, input, strlen(input));
            }
        }
    }

    sd = SSL_get_fd(ssl); /* get socket connection */
    SSL_free(ssl);        /* release SSL state */
    close(sd);            /* close connection */
}
