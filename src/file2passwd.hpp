
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include "compatibility_layer.hpp"
#include <string>
#include <vector>

/*! \mainpage
 *
 * \section intro_sec Introduction
 *
 * This program is a Fun project, to play around with modern c++, swig, python and CMake. \n
 * It doesn't make too much sense, but it can be used to generate a password from a file. \n
 * This can be used either in C++ or python.
 */

/**
* @class file2passwd
*
* @brief Main Class for generating a Password from a File.
*
* Use it as follows: \n
* file2passwd fpo("Path to File"); \n
* std::string passwd = fpo.get_passwd();
*/
class file2passwd {
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
  file2passwd(std::string path_to_file) : file_path(path_to_file), compat(path_to_file) {}

private:
  std::string file_path;
  compat_layer compat;
  std::string md5_from_file;

  std::string get_fibonacci_char_vector(void);
  std::string generate_passwd_from_file(int passwd_length);

  void handleErrors(void);
  int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
	      unsigned char *iv, unsigned char *ciphertext);
  std::string get_key(void);
  std::string get_iv(void);
};

#endif /* SRC_FILE2PASSWD_HPP_ */
