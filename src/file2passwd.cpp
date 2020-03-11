
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

  if (md5_hash_of_file != "")
    return md5_hash_of_file;

  md5_hash_of_file = compat.get_md5_hash_from_file();
  return md5_hash_of_file;
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

std::string File2Passwd::get_passwd(void)
{
  check_for_prerequisites();

  std::string key = get_key();
  std::string iv = get_iv();
  std::string plaintext = get_fibonacci_string();
  return compat.encrypt(key, iv, plaintext);
}

