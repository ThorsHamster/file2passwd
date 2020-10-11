
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

TEST_F(OpenSSLTests, get_md5_hash_from_file) {
  ConfigureUnitUnderTest();

  std::vector<char> file_buffer;

  //for testdata see md5.c
  EXPECT_EQ(unit_under_test_->get_md5_hash_from_file(file_buffer), "61626362626262626262626262626262");
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
