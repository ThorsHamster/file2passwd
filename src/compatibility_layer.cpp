#include "compatibility_layer.hpp"
#include "utilities.hpp"
#include "exception.hpp"
#include <sys/mman.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <openssl/md5.h>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <gsl/gsl>

/// @file
/// @brief This file contains a internal helper Class to be C++ compliant.

std::string CompatibilityLayer::get_md5_hash_from_file(void)
{
  if (!file_exists(file_path))
    {
      throw FileDoesNotExistException();
    }

  auto result = std::make_unique<unsigned char[]>(MD5_DIGEST_LENGTH);

  std::streamsize file_size = get_file_size();
  char file_buffer[file_size]; //NOLINT(cppcoreguidelines-avoid-c-arrays)
  get_file_buffer(file_size, file_buffer); //NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

  MD5((unsigned char*) file_buffer, file_size, result.get()); //NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
  munmap((char*)file_buffer, file_size);

  md5_from_file = convert_uchar_ptr_to_hex_string(result.get());

  return md5_from_file;
}

std::streamsize CompatibilityLayer::get_file_size(void)
{
  std::ifstream file;
  file.open(file_path, std::ios_base::in);
  file.ignore(std::numeric_limits<std::streamsize>::max());
  std::streamsize file_size = file.gcount();
  file.close();

  return file_size;
}

void CompatibilityLayer::get_file_buffer(std::streamsize file_size, char* file_buffer)
{
  std::ifstream file;
  file.open(file_path, std::ios_base::in | std::ios_base::binary);
  file.seekg( 0, std::ios_base::beg);
  file.read(file_buffer, file_size);
  file.close();
}

std::string CompatibilityLayer::convert_uchar_ptr_to_hex_string(unsigned char* result)
{
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
      ss << std::setw(2) << static_cast<unsigned>(result[i]); //NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
  return ss.str();
}

std::string CompatibilityLayer::encrypt(std::string key, std::string iv, std::string &plaintext)
{
  /* A 256 bit key */
  std::vector<unsigned char> key_uchar = string_to_unsigned_char(key);
  unsigned char *key_ = key_uchar.data();

  /* A 128 bit IV */
  std::vector<unsigned char> uv_uchar = string_to_unsigned_char(iv);
  unsigned char *iv_ = uv_uchar.data();

  /* Message to be encrypted */
  std::vector<unsigned char> msg_uchar = string_to_unsigned_char(plaintext);
  unsigned char *plaintext_ = msg_uchar.data();
    /*
   * Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, depending on the
   * algorithm and mode.
   */
  unsigned char ciphertext_[128];

  /* Encrypt the plaintext */
  openssl_encrypt(plaintext_, strlen ((char *)plaintext_), key_, iv_, ciphertext_);

  return convert_uchar_ptr_to_hex_string(ciphertext_);
}

int CompatibilityLayer::openssl_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
			 unsigned char *iv, unsigned char *ciphertext)
{
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

  return ciphertext_len;
}

void CompatibilityLayer::handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}

std::vector<unsigned char> CompatibilityLayer::string_to_unsigned_char(std::string const& str)
{
  auto vector_uchar = std::vector<unsigned char>(str.data(), str.data() + str.length());
  return std::move(vector_uchar);
}
