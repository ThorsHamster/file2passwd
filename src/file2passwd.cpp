
#include "file2passwd.hpp"
#include "compatibility_layer.hpp"
#include "utilities.hpp"
#include "exception.hpp"

/// @file
/// @brief This file contains the file2passwd main class

std::string File2Passwd::get_passwd(void)
{
  check_for_prerequisites();

  std::string key = get_key();
  std::string iv = get_iv();
  std::string plaintext = get_fibonacci_string();
  return compat.encrypt(key, iv, plaintext);
}

void File2Passwd::check_for_prerequisites(void)
{
  if (!file_exists(file_path))
    {
      throw FileDoesNotExistException();
    }
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

std::string File2Passwd::get_md5_hash(void)
{
  check_for_prerequisites();

  if (md5_hash_of_file != "")
    return md5_hash_of_file;

  md5_hash_of_file = compat.get_md5_hash_from_file();
  return md5_hash_of_file;
}

std::string File2Passwd::get_fibonacci_string(void)
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
  std::ifstream::pos_type length_of_file = ifs.tellg();
  std::vector<char> file_buffer(length_of_file);
  std::string result;

  auto fibonacci_numbers = get_fibonacci_vector_of_filesize(length_of_file);

  ifs.seekg(0, std::ios::beg);
  ifs.read(&file_buffer[0], length_of_file);

  for (size_t i=0; i<MAX_FIBONACCI_VALUE; i++)
    {
      if (fibonacci_numbers[i]==0)
      {
        break;
      }

      result.append(sizeof(char), file_buffer[fibonacci_numbers[i]]);
    }

  return result;
}

std::vector<uint64_t> File2Passwd::get_fibonacci_vector_of_filesize(std::ifstream::pos_type length_of_file)
{
  std::vector<uint64_t> fibonacci_numbers(MAX_FIBONACCI_VALUE);

  uint64_t fibonacci_number = 0;
  for (size_t i=1; fibonacci_number<=length_of_file; i++)
    {
      fibonacci_number = fibonacci(i);
      fibonacci_numbers[i-1] = fibonacci_number;
    }

  return fibonacci_numbers;
}
