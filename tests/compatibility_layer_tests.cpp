
#include <limits.h>
#include <string.h>
#include "compatibility_layer.hpp"
#include "gtest/gtest.h"

namespace {
  TEST(TEST_get_md5_hash_from_file, Trivial) {
    CompatibilityLayer compat("LICENSE");
    const std::string expected_string = "5cbe034c343ead03a139a598a5d27d55";
    const std::string result = compat.get_md5_hash_from_file();
    EXPECT_EQ(result, expected_string);
  }

  TEST(TEST_convert_uchar_ptr_to_hex_string, Trivial) {
    CompatibilityLayer compat("LICENSE");
    // see here for ascii table: https://www.torsten-horn.de/techdocs/ascii.htm
    // 1 equals 31.. a equals 61
    const std::string expected_string = "31323361626364000000000000000000";

    std::string test_string = "123abcd";
    auto test_vector = std::vector<unsigned char>(test_string.data(), test_string.data() + test_string.length());
    const std::string result = compat.convert_uchar_ptr_to_hex_string(test_vector.data());
    EXPECT_EQ(result, expected_string);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
