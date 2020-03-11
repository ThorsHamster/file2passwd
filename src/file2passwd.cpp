
#include "file2passwd.hpp"
#include "compatibility_layer.hpp"
#include "utilities.hpp"
#include "exception.hpp"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

/// @file
/// @brief This file contains the file2passwd main class

std::string File2Passwd::get_md5_hash(void)
{
  check_for_prerequisites();

  return compat.get_md5_hash_from_file();
}

void File2Passwd::check_for_prerequisites(void)
{
  if (!file_exists(file_path))
    {
      throw FileDoesNotExistException();
    }
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

std::vector<unsigned char> string_to_unsigned_char(std::string const& str)
{
  auto vector_uchar = std::vector<unsigned char>(str.data(), str.data() + str.length());
  return std::move(vector_uchar);
}

std::string File2Passwd::get_passwd(void)
{
  check_for_prerequisites();

  /* A 256 bit key */
  std::vector<unsigned char> key_uchar = string_to_unsigned_char(get_key());
  unsigned char *key = key_uchar.data();

  /* A 128 bit IV */
  std::vector<unsigned char> uv_uchar = string_to_unsigned_char(get_iv());
  unsigned char *iv = uv_uchar.data();

  /* Message to be encrypted */
  std::vector<unsigned char> msg_uchar = string_to_unsigned_char(get_fibonacci_string());
  unsigned char *plaintext = msg_uchar.data();

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
  compat.encrypt(plaintext, strlen ((char *)plaintext), key, iv,
			    ciphertext);

  return compat.convert_uchar_ptr_to_hex_string(ciphertext);
}

