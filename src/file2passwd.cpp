
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

  std::vector<char> file_buffer = file_reader_->get_file_buffer();
  return open_ssl_->get_md5_hash_from_file(file_buffer);
}

auto File2PasswdInternal::get_fibonacci_vector_of_filelength(void) -> std::vector<uint64_t> {
  std::vector<uint64_t> fibonacci_numbers(utilities_->get_max_fibonacci_value());

  uint64_t fibonacci_number = 0;
  for (size_t i = 1; fibonacci_number <= file_reader_->get_file_size(); i++) {
    fibonacci_number = utilities_->fibonacci(i);
    fibonacci_numbers[i - 1] = fibonacci_number;

    if (i >= utilities_->get_max_fibonacci_value())
      break;
  }

  return fibonacci_numbers;
}

auto File2PasswdInternal::get_fibonacci_string(void) -> std::string {
  std::string result;

  std::vector<char> file_buffer = file_reader_->get_file_buffer();
  std::vector<uint64_t> fibonacci_numbers = get_fibonacci_vector_of_filelength();

  for (size_t i = 0; i < utilities_->get_max_fibonacci_value(); i++) {
    if (fibonacci_numbers[i] == 0)
      break;

    result.append(sizeof(char), file_buffer[fibonacci_numbers[i]]);
  }

  return result;
}

}  // namespace file2passwd