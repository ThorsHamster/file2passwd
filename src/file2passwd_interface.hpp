#ifndef SRC_FILE2PASSWD_INTERFACE_HPP_
#define SRC_FILE2PASSWD_INTERFACE_HPP_

#include "file2passwd.hpp"

namespace file2passwd {

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
  explicit File2Passwd(const std::string &path_to_file);

 private:
  std::unique_ptr<file2passwd::File2PasswdInternal> file2passwd_;
};

}  // namespace file2passwd

#endif
