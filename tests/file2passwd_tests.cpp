
#include <limits.h>
#include <string.h>
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
    const std::string expected_string = "File does not exist.";
    const std::string result = fpo.get_md5_hash();
    EXPECT_EQ(result, expected_string);
  }

  TEST(TEST_get_md5_hash_from_file, get_local_copy_of_md5hash_at_second_time) {
    File2Passwd fpo("LICENSE");
    const std::string expected_string = "5cbe034c343ead03a139a598a5d27d55";
    fpo.get_md5_hash();
    const std::string result = fpo.get_md5_hash();
    EXPECT_EQ(result, expected_string);
  }

  TEST(TEST_get_passwd, File_existent) {
      File2Passwd fpo("LICENSE");
      const std::string expected_string = "1eeb22037fbc98193fbd60f6cad7ec6c";
      const std::string result = fpo.get_passwd();
      EXPECT_EQ(result, expected_string);
    }

  TEST(TEST_get_passwd, File_not_existent) {
      File2Passwd fpo("File_not_existent");
      const std::string expected_string = "File does not exist.";
      const std::string result = fpo.get_passwd();
      EXPECT_EQ(result, expected_string);
    }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
