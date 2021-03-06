
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "exception.hpp"
#include "file2passwd.hpp"
#include "gtest/gtest.h"
#include "mock_file_reader.hpp"
#include "mock_openssl.hpp"
#include "mock_utilities.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class File2PasswdTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    ON_CALL(*mock_file_reader_, file_exists())
        .WillByDefault(Return(false));
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<file2passwd::File2PasswdInternal>(std::move(mock_utilities_),
                                                                          std::move(mock_file_reader_),
                                                                          std::move(mock_open_ssl_));
  }

  std::unique_ptr<utilities::MockUtilities> mock_utilities_ = std::make_unique<NiceMock<utilities::MockUtilities>>();
  std::unique_ptr<filereader::MockFileReader> mock_file_reader_ = std::make_unique<NiceMock<filereader::MockFileReader>>("<File>");
  std::unique_ptr<openssl::MockOpenSSL> mock_open_ssl_ = std::make_unique<NiceMock<openssl::MockOpenSSL>>();
  std::unique_ptr<file2passwd::File2PasswdInternal> unit_under_test_;
};

TEST_F(File2PasswdTests, get_md5_hash_happy_path) {
  ON_CALL(*mock_open_ssl_, get_md5_hash_from_file(_))
      .WillByDefault(Return("md5_hash"));
  ON_CALL(*mock_file_reader_, file_exists())
      .WillByDefault(Return(true));
  ON_CALL(*mock_file_reader_, get_file_size())
      .WillByDefault(Return(10));

  ConfigureUnitUnderTest();

  auto result = unit_under_test_->get_md5_hash();
  const std::string expected_string = "md5_hash";

  EXPECT_EQ(result, expected_string);
}

TEST_F(File2PasswdTests, get_md5_hash_file_does_not_exist) {
  ON_CALL(*mock_file_reader_, file_exists())
      .WillByDefault(Return(false));

  ConfigureUnitUnderTest();

  EXPECT_THROW(unit_under_test_->get_md5_hash(), FileDoesNotExistException);
}

TEST_F(File2PasswdTests, get_md5_hash_file_is_empty) {
  ON_CALL(*mock_file_reader_, file_exists())
      .WillByDefault(Return(true));
  ON_CALL(*mock_file_reader_, get_file_size())
      .WillByDefault(Return(0));

  ConfigureUnitUnderTest();

  EXPECT_THROW(unit_under_test_->get_md5_hash(), FileIsEmpty);
}

TEST_F(File2PasswdTests, get_passwd_happy_path) {
  ON_CALL(*mock_file_reader_, file_exists())
      .WillByDefault(Return(true));
  std::vector<char> file_buffer = {'a', 'b', 'c', 'd', 'e'};
  ON_CALL(*mock_file_reader_, get_file_buffer())
      .WillByDefault(Return(file_buffer));
  ON_CALL(*mock_file_reader_, get_file_size())
      .WillByDefault(Return(10));
  ON_CALL(*mock_utilities_, get_max_fibonacci_value())
      .WillByDefault(Return(3));
  EXPECT_CALL(*mock_utilities_, fibonacci(_))
      .WillOnce(Return(1))
      .WillOnce(Return(2))
      .WillOnce(Return(3))
      .WillRepeatedly(Return(100));
  ON_CALL(*mock_open_ssl_, encrypt(_, _, _))
      .WillByDefault(Return("password"));

  ConfigureUnitUnderTest();

  auto result = unit_under_test_->get_passwd();
  const std::string expected_string = "password";

  EXPECT_EQ(result, expected_string);
}

TEST_F(File2PasswdTests, get_passwd_file_does_not_exist) {
  ON_CALL(*mock_file_reader_, file_exists())
      .WillByDefault(Return(false));

  ConfigureUnitUnderTest();

  EXPECT_THROW(unit_under_test_->get_passwd(), FileDoesNotExistException);
}

TEST_F(File2PasswdTests, get_passwd_file_is_empty) {
  ON_CALL(*mock_file_reader_, file_exists())
      .WillByDefault(Return(true));
  ON_CALL(*mock_file_reader_, get_file_size())
      .WillByDefault(Return(0));

  ConfigureUnitUnderTest();

  EXPECT_THROW(unit_under_test_->get_passwd(), FileIsEmpty);
}

TEST_F(File2PasswdTests, get_passwd_fibonacci_numbers_zero) {
  ON_CALL(*mock_file_reader_, file_exists())
      .WillByDefault(Return(true));
  std::vector<char> file_buffer = {'a', 'b', 'c', 'd', 'e'};
  ON_CALL(*mock_file_reader_, get_file_buffer())
      .WillByDefault(Return(file_buffer));
  ON_CALL(*mock_file_reader_, get_file_size())
      .WillByDefault(Return(10));
  ON_CALL(*mock_utilities_, get_max_fibonacci_value())
      .WillByDefault(Return(3));
  EXPECT_CALL(*mock_utilities_, fibonacci(_))
      .WillOnce(Return(1))
      .WillOnce(Return(200))
      .WillRepeatedly(Return(100));
  ON_CALL(*mock_open_ssl_, encrypt(_, _, _))
      .WillByDefault(Return("password"));

  ConfigureUnitUnderTest();

  auto result = unit_under_test_->get_passwd();
  const std::string expected_string = "password";

  EXPECT_EQ(result, expected_string);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
