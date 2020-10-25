
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "file_reader.hpp"
#include "gtest/gtest.h"

namespace {

class FileReaderTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    unit_under_test_ = std::make_unique<filereader::FileReader>("LICENSE");
  }

  std::unique_ptr<filereader::FileReader> unit_under_test_;
};

TEST_F(FileReaderTests, file_exists_Exists) {
  EXPECT_EQ(unit_under_test_->file_exists(), true);
}

TEST_F(FileReaderTests, file_exists_Doesnt_Exists) {
  unit_under_test_ = std::make_unique<filereader::FileReader>("File_does_not_exist");
  EXPECT_EQ(unit_under_test_->file_exists(), false);
}

TEST_F(FileReaderTests, get_file_buffer_check_that_elements_are_in_valid_range) {
  ASSERT_THAT(unit_under_test_->get_file_buffer(), testing::Each(testing::AllOf(testing::Gt(0), testing::Lt(127))));
}

TEST_F(FileReaderTests, get_file_buffer_not_existing_file_empty_vector) {
  unit_under_test_ = std::make_unique<filereader::FileReader>("File_does_not_exist");
  ASSERT_THAT(unit_under_test_->get_file_buffer(), testing::ElementsAre());
}

TEST_F(FileReaderTests, get_file_size_not_empty) {
  EXPECT_GT(unit_under_test_->get_file_size(), 0);
}

TEST_F(FileReaderTests, get_file_size_empty) {
  unit_under_test_ = std::make_unique<filereader::FileReader>("File_does_not_exist");
  EXPECT_EQ(unit_under_test_->get_file_size(), 0);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
