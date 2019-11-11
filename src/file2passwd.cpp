
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

#define MAX_FIBONACCI_VALUE 51

file2passwd::file2passwd(std::string argv_file_path)
{
  file_path = argv_file_path;
}

std::string file2passwd::get_md5_hash_from_file(void)
{
  if (!file_exists(file_path))
    {
      return "";
    }

  compat_layer compat(file_path);
  md5_from_file = compat.get_md5_hash_from_file();
  return md5_from_file;
}

uint64_t file2passwd::fibonacci(uint64_t number)
{
  if (number <= 0 or number >= MAX_FIBONACCI_VALUE)
    {
      return 0;
    }

  uint64_t f_n_2 = 1;
  uint64_t f_n_1 = 0;
  uint64_t f_n = 0;
  // f_n = f_(n-1) + f_(n-2) for n>=3
  for (int i=1; i<=number; i++)
    {
      f_n = f_n_1 + f_n_2;
      f_n_2 = f_n_1;
      f_n_1 = f_n;
    }

  return f_n;
}

std::string file2passwd::get_fibonacci_char_vector(void)
{
  if (!file_exists(file_path))
    {
      return "";
    }

  std::ifstream ifs(file_path, std::ios::binary|std::ios::ate);
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

std::string file2passwd::get_key(void)
{
  //return a 256 Bit representation of md5 hash
  std::string key = get_md5_hash_from_file();
  key.append("\0");
  return key.substr(0, 32);
}

std::string file2passwd::get_iv(void)
{
  //return a 128 Bit representation of md5 hash
  std::string iv = get_md5_hash_from_file();
  iv.append("\0");
  return iv.substr(0, 16);
}

std::string file2passwd::get_passwd(void)
{
  /* A 256 bit key */
  unsigned char *key = (unsigned char *)get_key().c_str();

  /* A 128 bit IV */
  unsigned char *iv = (unsigned char *)get_iv().c_str();

  /* Message to be encrypted */
  unsigned char *plaintext =
      (unsigned char *)get_fibonacci_char_vector().c_str();

  std::cout << "'" << get_key().c_str() << "'" << "\n";
  std::cout << "'" << get_iv().c_str() <<  "'" <<  "\n";
  std::cout << "'" << get_fibonacci_char_vector().c_str() << "'" <<  "\n";

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

  /* Do something useful with the ciphertext here */
  printf("Ciphertext is:\n");
  BIO_dump_fp (stdout, (const char *)ciphertext, ciphertext_len);
  std::cout << "ciphertext:" <<  ciphertext << "\n";

  return "";
}

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
