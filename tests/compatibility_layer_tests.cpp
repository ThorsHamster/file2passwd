
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
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<compatlayer::CompatibilityLayer>();
    unit_under_test_->init(std::move(mock_utilities_), std::move(mock_file_reader_), std::move(mock_open_ssl_));
  }

  std::unique_ptr<utilities::MockUtilities> mock_utilities_ = std::make_unique<NiceMock<utilities::MockUtilities>>();
  std::unique_ptr<filereader::MockFileReader> mock_file_reader_ = std::make_unique<NiceMock<filereader::MockFileReader>>("<File>");
  std::unique_ptr<openssl::MockOpenSSL> mock_open_ssl_ = std::make_unique<NiceMock<openssl::MockOpenSSL>>();
  std::unique_ptr<compatlayer::CompatibilityLayer> unit_under_test_;
};

TEST_F(CompatibilityLayerTests, get_md5_hash_from_file_trivial) {
  ON_CALL(*mock_file_reader_, file_exists())
      .WillByDefault(Return(true));

  ConfigureUnitUnderTest();

  // for test data, see stub of md5.c
  const std::string expected_string = "61626362626262626262626262626262";
  const std::string result = unit_under_test_->get_md5_hash_from_file();
  EXPECT_EQ(result, expected_string);
}

TEST_F(CompatibilityLayerTests, get_md5_hash_from_file_file_does_not_exist) {
  ON_CALL(*mock_file_reader_, file_exists())
      .WillByDefault(Return(false));

  ConfigureUnitUnderTest();

  EXPECT_THROW(unit_under_test_->get_md5_hash_from_file(), FileDoesNotExistException);
}

TEST_F(CompatibilityLayerTests, convert_uchar_ptr_to_hex_string_trivial) {
  ConfigureUnitUnderTest();
  // see here for ascii table: https://www.torsten-horn.de/techdocs/ascii.htm
  // 1 equals 31.. a equals 61
  const std::string expected_string = "30313233616263643031323361626364";

  std::string test_string = "0123abcd0123abcd";
  auto test_vector = std::vector<unsigned char>(test_string.data(), test_string.data() + test_string.length());
  const std::string result = unit_under_test_->convert_uchar_ptr_to_hex_string(test_vector.data());
  EXPECT_EQ(result, expected_string);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
