#ifndef SRC_COMPATLAYER_INTERFACE_HPP_
#define SRC_COMPATLAYER_INTERFACE_HPP_

#include "utilities.hpp"
#include "file_reader.hpp"

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

  virtual auto init(std::string file_path,
                    std::unique_ptr<utilities::UtilitiesInterface> utilities,
                    std::unique_ptr<filereader::FileReaderInterface> file_reader) -> void = 0;

  /// @brief Returns MD5 hash of file
  virtual auto get_md5_hash_from_file(void) -> std::string = 0;
  /// @brief Converts a unsigned char pointer to a hexidecimal std::string
  virtual auto convert_uchar_ptr_to_hex_string(unsigned char *result) -> std::string = 0;
  /// @brief Encrypts plaintext with OpenSSL. Needs key value and initialization vector iv
  virtual auto encrypt(const std::string &key, const std::string &iv, const std::string &plaintext) -> std::string = 0;

 protected:
  std::string file_path_;
  std::unique_ptr<utilities::UtilitiesInterface> utilities_;
  std::unique_ptr<filereader::FileReaderInterface> file_reader_;
};

}  // namespace compatlayer

#endif
