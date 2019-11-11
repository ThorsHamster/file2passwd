
#include <limits.h>
#include <string.h>
#include "file2passwd.hpp"
#include "gtest/gtest.h"

namespace {

  TEST(fibonacci_0, Trivial) {
    file2passwd fpo("LICENSE");
    EXPECT_EQ(0, fpo.fibonacci(0));
  }

  TEST(fibonacci_1, Trivial) {
    file2passwd fpo("LICENSE");
    EXPECT_EQ(1, fpo.fibonacci(1));
  }

  TEST(fibonacci_2, Trivial) {
    file2passwd fpo("LICENSE");
    EXPECT_EQ(1, fpo.fibonacci(2));
  }

  TEST(fibonacci_3, Trivial) {
    file2passwd fpo("LICENSE");
    EXPECT_EQ(2, fpo.fibonacci(3));
  }

  TEST(fibonacci_4, Trivial) {
    file2passwd fpo("LICENSE");
    EXPECT_EQ(3, fpo.fibonacci(4));
  }

  TEST(fibonacci_50, Trivial) {
    file2passwd fpo("LICENSE");
    EXPECT_EQ(12586269025, fpo.fibonacci(50));
  }

  TEST(fibonacci_51, Trivial) {
    file2passwd fpo("LICENSE");
    EXPECT_EQ(0, fpo.fibonacci(51));
  }

}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
