
#ifndef SRC_COMPATLAYER_HPP_
#define SRC_COMPATLAYER_HPP_

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <sys/mman.h>

#include <fstream>
#include <iomanip>
#include <iostream>

#include "compatibility_layer_interface.hpp"
#include "exception.hpp"
#include "utilities.hpp"

namespace compatlayer {

/**
* @class CompatibilityLayer
*
* @brief Internal helper Class to be C++ compliant.
*/
class CompatibilityLayer : public CompatibilityLayerInterface {
 public:
  explicit CompatibilityLayer() {}

  auto get_md5_hash_from_file(void) -> std::string override;
  auto convert_uchar_ptr_to_hex_string(unsigned char *result) -> std::string override;
  auto encrypt(const std::string &key, const std::string &iv, const std::string &plaintext) -> std::string override;

  auto init(std::string file_path,
            std::unique_ptr<utilities::UtilitiesInterface> utilities,
            std::unique_ptr<filereader::FileReader> file_reader) -> void override;

 private:
  std::string md5_from_file;

  void handleErrors(void);
  auto openssl_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                       unsigned char *iv, unsigned char *ciphertext) -> int;
  auto string_to_unsigned_char(std::string const &str) -> std::vector<unsigned char>;
};

}  // namespace compatlayer

#endif /* SRC_COMPATLAYER_HPP_ */
