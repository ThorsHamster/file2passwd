
#include "file2passwd.hpp"

#include "exception.hpp"
#include "utilities.hpp"

namespace file2passwd {

auto File2PasswdInternal::get_passwd(void) -> std::string {
  check_for_prerequisites();

  return open_ssl_->encrypt(get_fibonacci_string(), get_key(), get_iv());
}

void File2PasswdInternal::check_for_prerequisites(void) {
  if (!file_reader_->file_exists()) {
    throw FileDoesNotExistException();
  }
  if (file_reader_->get_file_size() == 0) {
    throw FileIsEmpty();
  }
}

auto File2PasswdInternal::get_key(void) -> std::string {
  //return a 256 Bit representation of md5 hash
  std::string key = get_md5_hash();
  return key.substr(0, 32);
}

auto File2PasswdInternal::get_iv(void) -> std::string {
  //return a 128 Bit representation of md5 hash
  std::string iv = get_md5_hash();
  iv = iv.substr(0, 16);
  return iv;
}

auto File2PasswdInternal::get_md5_hash(void) -> std::string {
  check_for_prerequisites();

  if (md5_hash_of_file != "")
    return md5_hash_of_file;

  std::vector<char> file_buffer = file_reader_->get_file_buffer();

  md5_hash_of_file = open_ssl_->get_md5_hash_from_file(file_buffer);
  return md5_hash_of_file;
}

auto File2PasswdInternal::get_fibonacci_string(void) -> std::string {
  /*
   * Opens the specified file and generates a vector with Fibonacci elements
   * as long as the Fibonacci element is smaller than the total size of the file.
   *
   * Then the bytes are taken from the file at the respective positions (fibonacci(i)) and joined together.
   */
  std::vector<char> file_buffer = file_reader_->get_file_buffer();

  auto fibonacci_numbers = get_fibonacci_vector_of_filelength(file_buffer.size());
  auto fibonacci_string = pick_chars_from_file(fibonacci_numbers, file_buffer);

  return fibonacci_string;
}

auto File2PasswdInternal::get_fibonacci_vector_of_filelength(std::ifstream::pos_type length_of_file) -> std::vector<uint64_t> {
  std::vector<uint64_t> fibonacci_numbers(utilities_->get_max_fibonacci_value());

  uint64_t fibonacci_number = 0;
  for (size_t i = 1; fibonacci_number <= length_of_file; i++) {
    fibonacci_number = utilities_->fibonacci(i);
    fibonacci_numbers[i - 1] = fibonacci_number;

    if (i >= utilities_->get_max_fibonacci_value())
      break;
  }

  return fibonacci_numbers;
}

auto File2PasswdInternal::pick_chars_from_file(std::vector<uint64_t> fibonacci_numbers, std::vector<char> &file_buffer) -> std::string {
  std::string result;

  for (size_t i = 0; i < utilities_->get_max_fibonacci_value(); i++) {
    if (fibonacci_numbers[i] == 0)
      break;

    result.append(sizeof(char), file_buffer[fibonacci_numbers[i]]);
  }

  return result;
}

}  // namespace file2passwd