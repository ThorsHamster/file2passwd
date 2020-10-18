#include "openssl.hpp"

#include <gsl/gsl>

namespace openssl {

auto OpenSSL::get_md5_hash_from_file(std::vector<char> file_buffer) -> std::string {
  auto result = std::make_unique<unsigned char[]>(MD5_DIGEST_LENGTH);

  MD5((unsigned char *)file_buffer.data(), file_buffer.size(), result.get());
  return convert_uchar_ptr_to_hex_string(result.get());
}

auto OpenSSL::convert_uchar_ptr_to_hex_string(unsigned char *result) -> std::string {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
    ss << std::setw(2) << static_cast<unsigned>(result[i]);  //NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  }
  return ss.str();
}

auto OpenSSL::encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                      unsigned char *iv, unsigned char *ciphertext) -> std::string {
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  /*
   * Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits
   */
  if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /*
   * Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /*
   * Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return convert_uchar_ptr_to_hex_string(ciphertext);
}

void OpenSSL::handleErrors(void) {
  ERR_print_errors_fp(stderr);
  throw OpenSSLException();
}

}  // namespace openssl