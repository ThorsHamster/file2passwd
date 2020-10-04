
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "file_reader.hpp"
#include "gtest/gtest.h"

namespace {

class FileReaderTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    unit_under_test_ = std::make_unique<filereader::FileReader>();
  }

  std::unique_ptr<filereader::FileReader> unit_under_test_;
};

TEST_F(FileReaderTests, file_exists_Exists) {
  EXPECT_EQ(unit_under_test_->file_exists("LICENSE"), true);
}

TEST_F(FileReaderTests, file_exists_Doesnt_Exists) {
  EXPECT_EQ(unit_under_test_->file_exists("LICENSE_notexistent"), false);
}

}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
