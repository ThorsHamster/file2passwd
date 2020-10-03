
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "compatibility_layer.hpp"
#include "gtest/gtest.h"
#include "mock_utilities.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class CompatibilityLayerTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*mock_utilities_, file_exists(_))
        .WillByDefault(Return(false));
    ON_CALL(*mock_utilities_, fibonacci(_))
        .WillByDefault(Return(0));
    ON_CALL(*mock_utilities_, get_max_fibonacci_value())
        .WillByDefault(Return(0));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<CompatibilityLayer>("LICENSE");
    unit_under_test_->inject_test_seam(std::move(mock_utilities_));
  }

  std::unique_ptr<MockUtilities> mock_utilities_ = std::make_unique<NiceMock<MockUtilities>>();
  std::unique_ptr<CompatibilityLayer> unit_under_test_;
};

TEST_F(CompatibilityLayerTests, get_md5_hash_from_file_trivial) {
  ON_CALL(*mock_utilities_, file_exists(_))
      .WillByDefault(Return(true));

  ConfigureUnitUnderTest();

  const std::string expected_string = "5cbe034c343ead03a139a598a5d27d55";
  const std::string result = unit_under_test_->get_md5_hash_from_file();
  EXPECT_EQ(result, expected_string);
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
