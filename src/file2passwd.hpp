#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "compatibility_layer.hpp"

/*! \mainpage
 *
 * \section intro_sec Introduction
 *
 * This program is a Fun project, to play around with modern c++, swig, python and CMake. \n
 * It doesn't make too much sense, but it can be used to generate a password from a file. \n
 * This can be used either in C++ or python. \n
 *
 *
 * How to use it as python binding: \n
 * ~~~~~~~~~~~~~{.py}
 * import pyfile2passwd
 *
 * fpo = pyfile2passwd.File2Passwd("/path_to_file/file")
 * print(fpo.get_passwd())
 * ~~~~~~~~~~~~~
 */

/**
* @class File2Passwd
*
* @brief Main Class for generating a Password from a File.
*
* Use it as follows: \n
* File2Passwd fpo("Path to File"); \n
* std::string passwd = fpo.get_passwd();
*/
class File2Passwd {
 public:
  /// @brief Returns MD5 hash of file
  auto get_md5_hash(void) -> std::string;
  /// @brief Returns password generated out of file
  auto get_passwd(void) -> std::string;

  /// @brief Construct object
  ///
  /// @pre The file should be existent.
  ///
  /// @param path_to_file Absolute Path to File
  ///
  explicit File2Passwd(const std::string &path_to_file) : file_path(path_to_file), compat(std::make_unique<CompatibilityLayer>(path_to_file)) {}

  auto inject_test_seam(std::unique_ptr<CompatibilityLayerInterface> compat_) -> void;

 private:
  std::string md5_hash_of_file;
  std::string file_path;
  std::unique_ptr<CompatibilityLayerInterface> compat;

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

#endif /* SRC_FILE2PASSWD_HPP_ */
