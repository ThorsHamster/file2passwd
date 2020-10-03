
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "exception.hpp"
#include "file2passwd.hpp"
#include "gtest/gtest.h"
#include "mock_compat_layer.hpp"
#include "mock_utilities.hpp"

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
    ON_CALL(*mock_compat_, encrypt(_, _, _))
        .WillByDefault(Return(""));
    ON_CALL(*mock_utilities_, file_exists(_))
        .WillByDefault(Return(false));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<file2passwd::File2PasswdInternal>();
    unit_under_test_->init("<File>", std::move(mock_compat_), std::move(mock_utilities_));
  }

  std::unique_ptr<compatlayer::MockCompatLayer> mock_compat_ = std::make_unique<NiceMock<compatlayer::MockCompatLayer>>();
  std::unique_ptr<utilities::MockUtilities> mock_utilities_ = std::make_unique<NiceMock<utilities::MockUtilities>>();
  std::unique_ptr<file2passwd::File2PasswdInternal> unit_under_test_;
};

TEST_F(File2PasswdTests, get_md5_hash) {
  ON_CALL(*mock_compat_, get_md5_hash_from_file())
      .WillByDefault(Return("md5_hash"));
  ON_CALL(*mock_utilities_, file_exists(_))
      .WillByDefault(Return(true));

  ConfigureUnitUnderTest();

  auto result = unit_under_test_->get_md5_hash();
  const std::string expected_string = "md5_hash";

  EXPECT_EQ(result, expected_string);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
