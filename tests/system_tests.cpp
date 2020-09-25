
#include <limits.h>
#include <string.h>

#include "exception.hpp"
#include "file2passwd.hpp"
#include "gtest/gtest.h"

namespace {
TEST(TEST_get_md5_hash_from_file, Trivial) {
  File2Passwd fpo("LICENSE");
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
