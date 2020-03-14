
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include "compatibility_layer.hpp"
#include <string>
#include <vector>
#include <fstream>

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
  std::string get_md5_hash(void);
  /// @brief Returns password generated out of file
  std::string get_passwd(void);

  /// @brief Construct object
  ///
  /// @pre The file should be existent.
  ///
  /// @param path_to_file Absolute Path to File
  ///
  explicit File2Passwd(const std::string& path_to_file) : file_path(path_to_file), compat(path_to_file) {}

private:
  std::string md5_hash_of_file;
  std::string file_path;
  CompatibilityLayer compat;

  void check_for_prerequisites(void);
  std::string get_fibonacci_char_vector(void);
  std::string generate_passwd_from_file(int passwd_length);

  std::string get_key(void);
  std::string get_iv(void);
  std::string get_fibonacci_string(void);
  std::vector<uint64_t> get_fibonacci_vector_of_filelength(std::ifstream::pos_type length_of_file);
  std::vector<char> read_file_into_filebuffer(std::ifstream &ifs, std::ifstream::pos_type length_of_file);
  std::string pick_chars_from_file(std::vector<uint64_t> fibonacci_numbers, std::vector<char> &file_buffer);
};

#endif /* SRC_FILE2PASSWD_HPP_ */
