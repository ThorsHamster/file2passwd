
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
  explicit CompatibilityLayer(std::unique_ptr<utilities::UtilitiesInterface> utilities,
                              std::unique_ptr<filereader::FileReaderInterface> file_reader,
                              std::unique_ptr<openssl::OpenSSLInterface> open_ssl) : utilities_(std::move(utilities)),
                                                                                     file_reader_(std::move(file_reader)),
                                                                                     open_ssl_(std::move(open_ssl)) {}

  auto encrypt(const std::string &key, const std::string &iv, const std::string &plaintext) -> std::string override;

 private:
  auto string_to_unsigned_char(std::string const &str) -> std::vector<unsigned char>;

  std::unique_ptr<utilities::UtilitiesInterface> utilities_;
  std::unique_ptr<filereader::FileReaderInterface> file_reader_;
  std::unique_ptr<openssl::OpenSSLInterface> open_ssl_;
};

}  // namespace compatlayer

#endif /* SRC_COMPATLAYER_HPP_ */
