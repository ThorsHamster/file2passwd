#ifndef SRC_COMPATLAYER_INTERFACE_HPP_
#define SRC_COMPATLAYER_INTERFACE_HPP_

#include "file_reader.hpp"
#include "openssl.hpp"
#include "utilities.hpp"

namespace compatlayer {

/**
* @class CompatibilityLayer
*
* @brief Internal helper Class to be C++ compliant.
*/
class CompatibilityLayerInterface {
 public:
  /// @brief Construct object
  ///
  /// @pre The file should be existent.
  ///
  /// @param path_to_file Absolute Path to File
  ///
  explicit CompatibilityLayerInterface() {}
  virtual ~CompatibilityLayerInterface() = default;

  virtual auto init(std::unique_ptr<utilities::UtilitiesInterface> utilities,
                    std::unique_ptr<filereader::FileReaderInterface> file_reader,
                    std::unique_ptr<openssl::OpenSSLInterface> open_ssl) -> void = 0;

  /// @brief Returns MD5 hash of file
  virtual auto get_md5_hash_from_file(void) -> std::string = 0;
  /// @brief Encrypts plaintext with OpenSSL. Needs key value and initialization vector iv
  virtual auto encrypt(const std::string &key, const std::string &iv, const std::string &plaintext) -> std::string = 0;

 protected:
  std::unique_ptr<utilities::UtilitiesInterface> utilities_;
  std::unique_ptr<filereader::FileReaderInterface> file_reader_;
  std::unique_ptr<openssl::OpenSSLInterface> open_ssl_;
};

}  // namespace compatlayer

#endif
