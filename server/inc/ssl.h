#ifndef __SSL__
#define __SSL__

#define FAIL -1     /*for error output == -1 */
#define BUFFER 1024 /*buffer for reading messages*/

#include "openssl/ssl.h"
#include "openssl/err.h"

/**

    @brief This function checks if the root user is executing the server.
    @return int Returns 1 if the root user is executing the server, and 0 if not.
**/
int isRoot();

/**
 * @brief initiliaze the SSL context for the server
 *  This function intitalizes the SSL conetext for the server, and sets the necessary options for secure communication
 * @param[ctx] ctx Pointer to the SSL context to be initialized.
 *  @param[CerFile] CertFile File path of the server's SSL certificate.
 * @param[KeyFile] KeyFile File path of the server's private key.
 * @return SSL_CTX*
 */

SSL_CTX *InitServerCTX(void);

/**

    @brief Load the SSL certificates for the server.
    This function loads the SSL certificate and private key for the server, and sets them in the SSL context.
    @param[ctx] ctx Pointer to the SSL context.
    @param[CertFile] CertFile File path of the server's SSL certificate.
    @param[KeyFile] KeyFile File path of the server's private key.

**/
void LoadCertificates(SSL_CTX *, char *, char *);

// void ShowCerts(SSL *);
// void Servlet(SSL *);

#endif //__SSL__