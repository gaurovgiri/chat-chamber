#include "ssl.h"

SSL_CTX *ctx;

void *InitCTX(void) /*creating and setting up ssl context structure*/

{
    SSL_METHOD *method;

    OpenSSL_add_all_algorithms(); /* Load cryptos, et.al. */

    SSL_load_error_strings(); /* Bring in and register error messages */

    method = TLSv1_2_client_method(); /* Create new client-method instance */

    ctx = SSL_CTX_new(method); /* Create new context */

    if (ctx == NULL)

    {

        ERR_print_errors_fp(stderr);

        abort();
    }
}

void ShowCerts(SSL *ssl) /*show the ceritficates to server and match them but here we are not using any client certificate*/

{
    X509 *cert;

    char *line;

    cert = SSL_get_peer_certificate(ssl); /* get the server's certificate */

    if (cert != NULL)

    {

        printf("Server certificates:\n");

        line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);

        printf("Subject: %s\n", line);

        free(line); /* free the malloc'ed string */

        line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);

        printf("Issuer: %s\n", line);

        free(line); /* free the malloc'ed string */

        X509_free(cert); /* free the malloc'ed certificate copy */
    }

    else

        printf("Info: No client certificates configured.\n");
}
