#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "compatibility_layer.hpp"
#include "utilities.hpp"

namespace file2passwd {

class File2PasswdInternal {
 public:
  auto get_md5_hash(void) -> std::string;
  auto get_passwd(void) -> std::string;

  explicit File2PasswdInternal(){};

  auto init(const std::string path_to_file,
            std::unique_ptr<compatlayer::CompatibilityLayerInterface> compat_,
            std::unique_ptr<utilities::UtilitiesInterface> utilities_) -> void;

 private:
  std::string md5_hash_of_file;
  std::string file_path;
  std::unique_ptr<compatlayer::CompatibilityLayerInterface> compat;
  std::unique_ptr<utilities::UtilitiesInterface> utilities;

  static constexpr int MAXIMUM_FILE_LENGTH = 1000000;

  void check_for_prerequisites(void);
  auto get_fibonacci_char_vector(void) -> std::string;
  auto generate_passwd_from_file(int passwd_length) -> std::string;

  auto get_key(void) -> std::string;
  auto get_iv(void) -> std::string;
  auto get_fibonacci_string(void) -> std::string;
  auto get_fibonacci_vector_of_filelength(std::ifstream::pos_type length_of_file) -> std::vector<uint64_t>;
  auto read_file_into_filebuffer(std::ifstream &ifs, std::ifstream::pos_type length_of_file) -> std::vector<char>;
  auto pick_chars_from_file(std::vector<uint64_t> fibonacci_numbers, std::vector<char> &file_buffer) -> std::string;
};

}  // namespace file2passwd

#endif /* SRC_FILE2PASSWD_HPP_ */
