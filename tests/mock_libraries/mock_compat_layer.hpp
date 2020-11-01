#ifndef MOCK_COMPATLAYER_HPP_
#define MOCK_COMPATLAYER_HPP_

#include <gmock/gmock.h>

#include "compatibility_layer_interface.hpp"

namespace compatlayer {

class MockCompatLayer : public CompatibilityLayerInterface {
 public:
  MockCompatLayer() : CompatibilityLayerInterface() {}
  MOCK_METHOD(std::string, encrypt, (const std::string &key, const std::string &iv, const std::string &plaintext), (override));
};

}  // namespace compatlayer

#endif