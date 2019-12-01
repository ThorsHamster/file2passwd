
#ifndef SRC_COMPATLAYER_HPP_
#define SRC_COMPATLAYER_HPP_

#include <string>

/**
* @class compat_layer
*
* @brief Internal helper Class to be C++ compliant.
*/
class compat_layer {
public:
  /// @brief Represents MD5 hash of file
  std::string md5_from_file;

  /// @brief Returns MD5 hash of file
  std::string get_md5_hash_from_file(void);
  /// @brief Converts a unsigned char pointer to a hexidecimal std::string
  std::string convert_uchar_ptr_to_hex_string(unsigned char* result);

  /// @brief Construct object
  ///
  /// @pre The file should be existent.
  ///
  /// @param path_to_file Absolute Path to File
  ///
  compat_layer(std::string path_to_file);

private:
  std::string file_path;

  std::streamsize get_file_size(void);
  void get_file_buffer(std::streamsize file_size, char* file_buffer);
};

#endif /* SRC_COMPATLAYER_HPP_ */
