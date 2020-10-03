
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "exception.hpp"
#include "file2passwd.hpp"
#include "gtest/gtest.h"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class SystemTests : public ::testing::Test {
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

TEST(TEST_get_md5_hash_from_file, Trivial) {
  file2passwd::File2PasswdInternal fpo("LICENSE");
  const std::string expected_string = "5cbe034c343ead03a139a598a5d27d55";
  const std::string result = fpo.get_md5_hash();
  EXPECT_EQ(result, expected_string);
}

TEST(TEST_get_md5_hash_from_file, File_not_existent) {
  File2Passwd fpo("File_not_existent");
  EXPECT_THROW(fpo.get_md5_hash(), FileDoesNotExistException);
}

TEST(TEST_get_passwd, complete_test) {
  File2Passwd fpo("LICENSE");
  const std::string expected_string = "1eeb22037fbc98193fbd60f6cad7ec6c";
  const std::string result = fpo.get_passwd();
  EXPECT_EQ(result, expected_string);
}

TEST(TEST_get_passwd, File_not_existent) {
  File2Passwd fpo("File_not_existent");
  EXPECT_THROW(fpo.get_md5_hash(), FileDoesNotExistException);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
