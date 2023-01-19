#ifndef __SSL__
#define __SSL__

#define FAIL -1 /*for error output == -1 */
#define BUFFER 1024 /*buffer for reading messages*/

#include "openssl/ssl.h"
#include "openssl/err.h"


int OpenListener(int);
int isRoot();
SSL_CTX *InitServerCTX(void);
void LoadCertificates(SSL_CTX *, char *, char *);
void ShowCerts(SSL *);
void Servlet(SSL *);

#endif //__SSL__