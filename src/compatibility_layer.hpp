
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
  auto get_md5_hash_from_file(void) -> std::string;
  /// @brief Converts a unsigned char pointer to a hexidecimal std::string
  auto convert_uchar_ptr_to_hex_string(unsigned char *result) -> std::string;
  /// @brief Encrypts plaintext with OpenSSL. Needs key value and initialization vector iv
  auto encrypt(const std::string &key, const std::string &iv, const std::string &plaintext) -> std::string;
  /// @brief Construct object
  ///
  /// @pre The file should be existent.
  ///
  /// @param path_to_file Absolute Path to File
  ///
  explicit CompatibilityLayer(const std::string &path_to_file) : file_path(path_to_file) {}

 private:
  /// @brief Represents MD5 hash of file
  std::string md5_from_file;
  std::string file_path;

  auto get_file_size(void) -> std::streamsize;
  void get_file_buffer(std::streamsize file_size, char *file_buffer);

  void handleErrors(void);
  auto openssl_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                      unsigned char *iv, unsigned char *ciphertext) -> int;
  auto string_to_unsigned_char(std::string const &str) -> std::vector<unsigned char>;
};

#endif /* SRC_COMPATLAYER_HPP_ */
