
#include <limits.h>
#include <string.h>
#include <gmock/gmock.h>
#include "gtest/gtest.h"

#include "exception.hpp"
#include "file2passwd.hpp"
#include "mock_compat_layer.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class File2PasswdTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*mock_compat_, get_md5_hash_from_file())
        .WillByDefault(Return(""));
    ON_CALL(*mock_compat_, convert_uchar_ptr_to_hex_string(_))
        .WillByDefault(Return(""));
    ON_CALL(*mock_compat_, encrypt(_, _ ,_))
        .WillByDefault(Return(""));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<File2Passwd>("LICENSE");
    unit_under_test_->inject_test_seam(std::move(mock_compat_));
  }

  uint8_t i2c_address_ = 0x68;
  std::unique_ptr<MockCompatLayer> mock_compat_ = std::make_unique<NiceMock<MockCompatLayer>>();
  std::unique_ptr<File2Passwd> unit_under_test_;
};

TEST(TEST_get_md5_hash_from_file, Trivial) {
  File2Passwd fpo("LICENSE");
  const std::string expected_string = "5cbe034c343ead03a139a598a5d27d55";
  const std::string result = fpo.get_md5_hash();
  EXPECT_EQ(result, expected_string);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
