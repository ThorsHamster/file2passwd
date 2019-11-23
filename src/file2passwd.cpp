
#include "file2passwd.hpp"
#include "compatibility_layer.hpp"
#include "utilities.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
#include <string.h>

/// @file
/// @brief This file contains the file2passwd main class

/*! \mainpage
 *
 * \section intro_sec Introduction
 *
 * This program is a Fun project, to play around with modern c++, swig, python and CMake. \n
 * It doesn't make too much sense, but it can be used to generate a password from a file. \n
 * This can be used either in C++ or python.
 */

/**
* @class file2passwd
*
* @brief Main Class for generating a Password from a File.
*
* Use it as follows: \n
* file2passwd fpo("Path to File"); \n
* std::string passwd = fpo.get_passwd();
*/

/// @brief Returns MD5 hash of file
std::string file2passwd::get_md5_hash(void)
{
  if (!file_exists(file_path))
    {
      return "File does not exist.";
    }

  if (md5_from_file != "")
    return md5_from_file;

  md5_from_file = compat.get_md5_hash_from_file();
  return md5_from_file;
}

/// @brief Creates a vector of chars of a File.
/// Takes char from File at position of fibonacci(number)
std::string file2passwd::get_fibonacci_char_vector(void)
{
  std::ifstream ifs(file_path, std::ios::binary | std::ios::ate);
  std::ifstream::pos_type pos = ifs.tellg();

  std::vector<uint64_t> fibonacci_numbers(MAX_FIBONACCI_VALUE);

  uint64_t fib_number=0;
  for (size_t i=1; fib_number<=pos; i++)
    {
      fib_number=fibonacci(i);
      fibonacci_numbers[i-1] = fib_number;
    }

  std::vector<char> file_buffer(pos);
  std::string result;

  ifs.seekg(0, std::ios::beg);
  ifs.read(&file_buffer[0], pos);

  for (size_t i=0; i<MAX_FIBONACCI_VALUE; i++)
    {
      if (fibonacci_numbers[i]==0)
	{
	  break;
	}

      result.append(sizeof(char),file_buffer[fibonacci_numbers[i]]);
    }

  return result;
}

/// @brief Returns key for AES encryption
std::string file2passwd::get_key(void)
{
  //return a 256 Bit representation of md5 hash
  std::string key = get_md5_hash();
  return key.substr(0, 32);
}

/// @brief Returns initialization vector (iv) for AES encryption
std::string file2passwd::get_iv(void)
{
  //return a 128 Bit representation of md5 hash
  std::string iv = get_md5_hash();
  iv = iv.substr(0, 16);
  return iv;
}

/// @brief Returns password generated out of file
std::string file2passwd::get_passwd(void)
{
  if (!file_exists(file_path))
    {
      return "File does not exist.";
    }

  /* A 256 bit key */
  std::string key_s = get_key();
  char key_char[key_s.size() + 1];
  strcpy(key_char, key_s.c_str());
  unsigned char *key = reinterpret_cast<unsigned char*>(key_char);

  /* A 128 bit IV */
  std::string iv_s = get_iv();
  char iv_char[iv_s.size() + 1];
  strcpy(iv_char, iv_s.c_str());
  unsigned char *iv = reinterpret_cast<unsigned char*>(iv_char);

  /* Message to be encrypted */
  unsigned char *plaintext =
      (unsigned char *)get_fibonacci_char_vector().c_str();

  /*
   * Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, depending on the
   * algorithm and mode.
   */
  unsigned char ciphertext[128];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[128];

  int decryptedtext_len, ciphertext_len;

  /* Encrypt the plaintext */
  ciphertext_len = encrypt (plaintext, strlen ((char *)plaintext), key, iv,
			    ciphertext);

  return compat.convert_uchar_ptr_to_hex_string(ciphertext);
}

/// @brief Encrypts char vector taken from File
int file2passwd::encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
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

void file2passwd::handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}
