#include "md5.h"

unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md) {
  return "";
}

void ERR_print_errors_fp(FILE *fp) {
}

EVP_CIPHER_CTX *EVP_CIPHER_CTX_new(void) {
}

const EVP_CIPHER *EVP_aes_256_cbc(void) {
}

int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx,
                       const EVP_CIPHER *cipher, ENGINE *impl,
                       const unsigned char *key,
                       const unsigned char *iv) {
  return 0;
}

int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out,
                      int *outl, const unsigned char *in, int inl) {
  return 0;
}

int EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx, unsigned char *out,
                        int *outl) {
  return 0;
}

void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *c) {
}
