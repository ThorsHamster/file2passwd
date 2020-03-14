
#ifndef SRC_COMPATLAYER_HPP_
#define SRC_COMPATLAYER_HPP_

#include <string>
#include <vector>

/**
* @class CompatibilityLayer
*
* @brief Internal helper Class to be C++ compliant.
*/
class CompatibilityLayer {
public:
  /// @brief Returns MD5 hash of file
  std::string get_md5_hash_from_file(void);
  /// @brief Converts a unsigned char pointer to a hexidecimal std::string
  std::string convert_uchar_ptr_to_hex_string(unsigned char* result);
  /// @brief Encrypts plaintext with OpenSSL. Needs key value and initialization vector iv
  std::string encrypt(const std::string key, const std::string iv, std::string &plaintext);
  /// @brief Construct object
  ///
  /// @pre The file should be existent.
  ///
  /// @param path_to_file Absolute Path to File
  ///
  explicit CompatibilityLayer(const std::string& path_to_file) : file_path(path_to_file) {}

private:
  /// @brief Represents MD5 hash of file
  std::string md5_from_file;
  std::string file_path;

  std::streamsize get_file_size(void);
  void get_file_buffer(std::streamsize file_size, char* file_buffer);
  
  void handleErrors(void);
  int openssl_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
	      unsigned char *iv, unsigned char *ciphertext);
  std::vector<unsigned char> string_to_unsigned_char(std::string const& str);
};

#endif /* SRC_COMPATLAYER_HPP_ */
