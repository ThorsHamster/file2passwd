#include "md5.h"

unsigned char *MD5(const unsigned char *d, size_t n, unsigned char *md) {
  md[0] = 'a';
  md[1] = 'b';
  md[2] = 'c';
  md[3] = 'b';
  md[4] = 'b';
  md[5] = 'b';
  md[6] = 'b';
  md[7] = 'b';
  md[8] = 'b';
  md[9] = 'b';
  md[10] = 'b';
  md[11] = 'b';
  md[12] = 'b';
  md[13] = 'b';
  md[14] = 'b';
  md[15] = 'b';
  md[16] = 'b';
}

void ERR_print_errors_fp(FILE *fp) {
}

EVP_CIPHER_CTX *EVP_CIPHER_CTX_new(void) {
  return EVP_CIPHER_CTX_new_return;  //NOLINT only needed for unittests
}

const EVP_CIPHER *EVP_aes_256_cbc(void) {
}

int EVP_EncryptInit_ex(EVP_CIPHER_CTX *ctx,
                       const EVP_CIPHER *cipher, ENGINE *impl,
                       const unsigned char *key,
                       const unsigned char *iv) {
  return EVP_EncryptInit_ex_return;
}

int EVP_EncryptUpdate(EVP_CIPHER_CTX *ctx, unsigned char *out,
                      int *outl, const unsigned char *in, int inl) {
  out[0] = 'c';
  out[1] = 'c';
  out[2] = 'c';
  out[3] = 'c';
  out[4] = 'c';
  out[5] = 'c';
  out[6] = 'c';
  out[7] = 'c';
  out[8] = 'c';
  out[9] = 'c';
  out[10] = 'c';
  out[11] = 'c';
  out[12] = 'c';
  out[13] = 'c';
  out[14] = 'c';
  out[15] = 'c';
  out[16] = 'c';

  return EVP_EncryptUpdate_return;
}

int EVP_EncryptFinal_ex(EVP_CIPHER_CTX *ctx, unsigned char *out,
                        int *outl) {
  return EVP_EncryptFinal_ex_return;
}

void EVP_CIPHER_CTX_free(EVP_CIPHER_CTX *c) {
}
