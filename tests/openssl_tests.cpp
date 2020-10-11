
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "openssl.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class OpenSSLTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<openssl::OpenSSL>();
  }

  std::unique_ptr<openssl::OpenSSL> unit_under_test_;
};

TEST_F(OpenSSLTests, empty) {
  ConfigureUnitUnderTest();
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
