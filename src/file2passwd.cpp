
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

std::string File2Passwd::get_md5_hash(void)
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

std::string File2Passwd::get_fibonacci_char_vector(void)
{
  /*
   * Opens the specified file and generates a vector with Fibonacci elements
   * as long as the Fibonacci element is smaller than the total size of the file.
   *
   * for (int i=0; fibonacci(i)<file_size; i++)
   *
   * Then the bytes are taken from the file at the respective positions (fibonacci(i)) and joined together.
   */
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

std::string File2Passwd::get_key(void)
{
  //return a 256 Bit representation of md5 hash
  std::string key = get_md5_hash();
  return key.substr(0, 32);
}

std::string File2Passwd::get_iv(void)
{
  //return a 128 Bit representation of md5 hash
  std::string iv = get_md5_hash();
  iv = iv.substr(0, 16);
  return iv;
}

std::string File2Passwd::get_fibonacci_string(void)
{
  std::string fibonacci_string = get_fibonacci_char_vector();
  return fibonacci_string;
}

std::string File2Passwd::get_passwd(void)
{
  if (!file_exists(file_path))
    {
      return "File does not exist.";
    }

  /* A 256 bit key */
  auto key_value = std::make_unique<char[]>(get_key().size());
  strcpy(key_value.get(), get_key().c_str());
  unsigned char *key = reinterpret_cast<unsigned char*>(key_value.get());

  /* A 128 bit IV */
  auto iv_value = std::make_unique<char[]>(get_iv().size());
  strcpy(iv_value.get(), get_iv().c_str());
  unsigned char *iv = reinterpret_cast<unsigned char*>(iv_value.get());

  /* Message to be encrypted */
  auto msg_value = std::make_unique<char[]>(get_fibonacci_string().size());
  strcpy(msg_value.get(), get_fibonacci_string().c_str());
  unsigned char *plaintext = reinterpret_cast<unsigned char*>(msg_value.get());

  /*
   * Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, depending on the
   * algorithm and mode.
   */
  unsigned char ciphertext[128];

  /* Buffer for the decrypted text */
  unsigned char decryptedtext[128];

  int decryptedtext_len;

  /* Encrypt the plaintext */
  encrypt (plaintext, strlen ((char *)plaintext), key, iv,
			    ciphertext);

  return compat.convert_uchar_ptr_to_hex_string(ciphertext);
}

int File2Passwd::encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
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

void File2Passwd::handleErrors(void)
{
  ERR_print_errors_fp(stderr);
  abort();
}
