
#include <limits.h>
#include <string.h>
#include "utilities.hpp"
#include "gtest/gtest.h"

namespace {
  TEST(file_exists, Exists) {
    EXPECT_EQ(file_exists("LICENSE"), true);
  }

  TEST(file_exists, Doesnt_Exists) {
    EXPECT_EQ(file_exists("LICENSE_notexistent"), false);
  }

  TEST(fibonacci, Trivial_0) {
    EXPECT_EQ(fibonacci(0), 0);
  }

  TEST(fibonacci, Trivial_1) {
    EXPECT_EQ(fibonacci(1), 1);
  }

  TEST(fibonacci, Trivial_2) {
    EXPECT_EQ(fibonacci(2), 1);
  }

  TEST(fibonacci, Trivial_3) {
    EXPECT_EQ(fibonacci(3), 2);
  }

  TEST(fibonacci, Trivial_4) {
    EXPECT_EQ(fibonacci(4), 3);
  }

  TEST(fibonacci, Trivial_50) {
    EXPECT_EQ(fibonacci(50), 12586269025);
  }

  TEST(fibonacci, Trivial_51) {
    EXPECT_EQ(fibonacci(51), 0);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
