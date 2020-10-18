#ifndef MOCK_OPENSSL_MD5_H_
#define MOCK_OPENSSL_MD5_H_

extern int EVP_CIPHER_CTX_new_return;
extern int EVP_EncryptInit_ex_return;
extern int EVP_EncryptUpdate_return;
extern int EVP_EncryptFinal_ex_return;

#ifdef __cplusplus
extern "C" {
#endif

#include "stddef.h"

#define MD5_DIGEST_LENGTH 16

unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md);

struct _IO_FILE;
struct _EVP_CIPHER_CTX;
struct _EVP_CIPHER;
struct _ENGINE;

typedef struct _IO_FILE FILE;
typedef struct _EVP_CIPHER_CTX EVP_CIPHER_CTX;
typedef struct _EVP_CIPHER EVP_CIPHER;
typedef struct _ENGINE ENGINE;

void ERR_print_errors_fp(FILE *fp);

EVP_CIPHER_CTX *EVP_CIPHER_CTX_new(void);

const EVP_CIPHER *EVP_aes_256_cbc(void);

int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx,
                       const EVP_CIPHER *cipher, ENGINE *impl,
                       const unsigned char *key,
                       const unsigned char *iv);

int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out,
                      int *outl, const unsigned char *in, int inl);

int EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx, unsigned char *out,
                        int *outl);

void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *c);

#ifdef __cplusplus
}
#endif

#endif