#ifndef __SSL__
#define __SSL__

#define FAIL -1     /*for error output == -1 */
#define BUFFER 1024 /*buffer for reading messages*/

#include "openssl/ssl.h"

extern SSL *ssl;
extern SSL_CTX *ctx;

int OpenConnection(const char *, int);

void *InitCTX(void); /*creating and setting up ssl context structure*/

void ShowCerts(SSL *);

#endif // __SSL__