
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
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
