#ifndef MOCK_COMPATLAYER_HPP_
#define MOCK_COMPATLAYER_HPP_

#include <gmock/gmock.h>

#include "compatibility_layer_interface.hpp"

namespace compatlayer {

class MockCompatLayer : public CompatibilityLayerInterface {
 public:
  MockCompatLayer() : CompatibilityLayerInterface() {}
  MOCK_METHOD(void, init, (std::unique_ptr<utilities::UtilitiesInterface> utilities, std::unique_ptr<filereader::FileReaderInterface> file_reader, std::unique_ptr<openssl::OpenSSLInterface> open_ssl), (override));
  MOCK_METHOD(std::string, get_md5_hash_from_file, (), (override));
  MOCK_METHOD(std::string, convert_uchar_ptr_to_hex_string, (unsigned char *result), (override));
  MOCK_METHOD(std::string, encrypt, (const std::string &key, const std::string &iv, const std::string &plaintext), (override));
};

}  // namespace compatlayer

#endif