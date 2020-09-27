#ifndef MOCK_COMPATLAYER_HPP_
#define MOCK_COMPATLAYER_HPP_

#include <gmock/gmock.h>
#include "compatibility_layer_interface.hpp"

class MockCompatLayer : public CompatibilityLayerInterface {
 public:
  MockCompatLayer() : CompatibilityLayerInterface("") {}
  MOCK_METHOD(std::string, get_md5_hash_from_file, (), (override));
  MOCK_METHOD(std::string, convert_uchar_ptr_to_hex_string, (unsigned char *result), (override));
  MOCK_METHOD(std::string, encrypt, (const std::string &key, const std::string &iv, const std::string &plaintext), (override));
};

#endif