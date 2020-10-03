
#ifndef SRC_COMPATLAYER_HPP_
#define SRC_COMPATLAYER_HPP_

#include "compatibility_layer_interface.hpp"

/**
* @class CompatibilityLayer
*
* @brief Internal helper Class to be C++ compliant.
*/
class CompatibilityLayer : public CompatibilityLayerInterface {
 public:
  explicit CompatibilityLayer(const std::string &path_to_file) : CompatibilityLayerInterface(path_to_file) {}

  auto get_md5_hash_from_file(void) -> std::string override;
  auto convert_uchar_ptr_to_hex_string(unsigned char *result) -> std::string override;
  auto encrypt(const std::string &key, const std::string &iv, const std::string &plaintext) -> std::string override;

  auto inject_test_seam(std::unique_ptr<utilities::UtilitiesInterface> utilities) -> void;

 private:
  std::string md5_from_file;

  static constexpr int MAXIMUM_FILE_LENGTH = 1000000;

  auto get_file_size(void) -> std::streamsize;
  void get_file_buffer(std::streamsize file_size, char *file_buffer);

  void handleErrors(void);
  auto openssl_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                       unsigned char *iv, unsigned char *ciphertext) -> int;
  auto string_to_unsigned_char(std::string const &str) -> std::vector<unsigned char>;
};

#endif /* SRC_COMPATLAYER_HPP_ */
