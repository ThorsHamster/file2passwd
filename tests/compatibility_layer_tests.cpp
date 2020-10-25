
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "compatibility_layer.hpp"
#include "exception.hpp"
#include "gtest/gtest.h"
#include "mock_file_reader.hpp"
#include "mock_openssl.hpp"
#include "mock_utilities.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class CompatibilityLayerTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*mock_utilities_, fibonacci(_))
        .WillByDefault(Return(0));
    ON_CALL(*mock_utilities_, get_max_fibonacci_value())
        .WillByDefault(Return(0));
    ON_CALL(*mock_file_reader_, file_exists())
        .WillByDefault(Return(false));
    ON_CALL(*mock_open_ssl_, get_md5_hash_from_file(_))
        .WillByDefault(Return(""));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<compatlayer::CompatibilityLayer>(std::move(mock_utilities_),
                                                                         std::move(mock_file_reader_),
                                                                         std::move(mock_open_ssl_));
  }

  std::unique_ptr<utilities::MockUtilities> mock_utilities_ = std::make_unique<NiceMock<utilities::MockUtilities>>();
  std::unique_ptr<filereader::MockFileReader> mock_file_reader_ = std::make_unique<NiceMock<filereader::MockFileReader>>("<File>");
  std::unique_ptr<openssl::MockOpenSSL> mock_open_ssl_ = std::make_unique<NiceMock<openssl::MockOpenSSL>>();
  std::unique_ptr<compatlayer::CompatibilityLayer> unit_under_test_;
};

TEST_F(CompatibilityLayerTests, get_md5_hash_from_file_happy_path) {
  ON_CALL(*mock_open_ssl_, get_md5_hash_from_file(_))
      .WillByDefault(Return("61626362626262626262626262626262"));

  ConfigureUnitUnderTest();

  // for test data, see stub of md5.c
  const std::string expected_string = "61626362626262626262626262626262";
  const std::string result = unit_under_test_->get_md5_hash_from_file();
  EXPECT_EQ(result, expected_string);
}

TEST_F(CompatibilityLayerTests, encrypt_happy_path) {
  ON_CALL(*mock_open_ssl_, encrypt(_, _, _))
      .WillByDefault(Return("password"));

  ConfigureUnitUnderTest();

  std::string key = "key";
  std::string iv = "iv";
  std::string plaintext = "plaintext";

  EXPECT_EQ(unit_under_test_->encrypt(key, iv, plaintext), "password");
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
