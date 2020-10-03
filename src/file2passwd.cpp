
#include "file2passwd.hpp"

#include "compatibility_layer.hpp"
#include "exception.hpp"
#include "utilities.hpp"

namespace file2passwd {

File2PasswdInternal::File2PasswdInternal(const std::string &path_to_file) {
  file_path = path_to_file;
  utilities = std::make_unique<utilities::Utilities>();
  compat = std::make_unique<compatlayer::CompatibilityLayer>();
  compat->init(path_to_file, std::make_unique<utilities::Utilities>());
}

auto File2PasswdInternal::get_passwd(void) -> std::string {
  check_for_prerequisites();

  std::string key = get_key();
  std::string iv = get_iv();
  std::string plaintext = get_fibonacci_string();
  return compat->encrypt(key, iv, plaintext);
}

void File2PasswdInternal::check_for_prerequisites(void) {
  if (!utilities->file_exists(file_path)) {
    throw FileDoesNotExistException();
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

  md5_hash_of_file = compat->get_md5_hash_from_file();
  return md5_hash_of_file;
}

auto File2PasswdInternal::get_fibonacci_string(void) -> std::string {
  /*
   * Opens the specified file and generates a vector with Fibonacci elements
   * as long as the Fibonacci element is smaller than the total size of the file.
   *
   * Then the bytes are taken from the file at the respective positions (fibonacci(i)) and joined together.
   */
  std::ifstream ifs(file_path, std::ios::binary | std::ios::ate);
  std::ifstream::pos_type length_of_file = ifs.tellg();

  auto fibonacci_numbers = get_fibonacci_vector_of_filelength(length_of_file);
  auto file_buffer = read_file_into_filebuffer(ifs, length_of_file);
  auto fibonacci_string = pick_chars_from_file(fibonacci_numbers, file_buffer);

  return fibonacci_string;
}

auto File2PasswdInternal::get_fibonacci_vector_of_filelength(std::ifstream::pos_type length_of_file) -> std::vector<uint64_t> {
  std::vector<uint64_t> fibonacci_numbers(utilities->get_max_fibonacci_value());

  uint64_t fibonacci_number = 0;
  for (size_t i = 1; fibonacci_number <= length_of_file; i++) {
    fibonacci_number = utilities->fibonacci(i);
    fibonacci_numbers[i - 1] = fibonacci_number;
  }

  return fibonacci_numbers;
}

auto File2PasswdInternal::read_file_into_filebuffer(std::ifstream &ifs, std::ifstream::pos_type length_of_file) -> std::vector<char> {
  if (length_of_file <= 0 or length_of_file >= MAXIMUM_FILE_LENGTH) {
    return std::vector<char>{};
  }

  std::vector<char> file_buffer(length_of_file);

  ifs.seekg(0, std::ios::beg);
  ifs.read(&file_buffer[0], length_of_file);

  return std::move(file_buffer);
}

auto File2PasswdInternal::pick_chars_from_file(std::vector<uint64_t> fibonacci_numbers, std::vector<char> &file_buffer) -> std::string {
  std::string result;

  for (size_t i = 0; i < utilities->get_max_fibonacci_value(); i++) {
    if (fibonacci_numbers[i] == 0) {
      break;
    }

    result.append(sizeof(char), file_buffer[fibonacci_numbers[i]]);
  }

  return result;
}

auto File2PasswdInternal::inject_test_seam(std::unique_ptr<compatlayer::CompatibilityLayerInterface> compat_) -> void {
  compat = std::move(compat_);
}

}  // namespace file2passwd