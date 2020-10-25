
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "gtest/gtest.h"
#include "utilities.hpp"

namespace {

class UtilityTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
    unit_under_test_ = std::make_unique<utilities::Utilities>();
  }

  std::unique_ptr<utilities::Utilities> unit_under_test_;
};

TEST_F(UtilityTests, fibonacci_0) {
  EXPECT_EQ(unit_under_test_->fibonacci(0), 0);
}

TEST_F(UtilityTests, fibonacci_1) {
  EXPECT_EQ(unit_under_test_->fibonacci(1), 1);
}

TEST_F(UtilityTests, fibonacci_2) {
  EXPECT_EQ(unit_under_test_->fibonacci(2), 1);
}

TEST_F(UtilityTests, fibonacci_3) {
  EXPECT_EQ(unit_under_test_->fibonacci(3), 2);
}

TEST_F(UtilityTests, fibonacci_4) {
  EXPECT_EQ(unit_under_test_->fibonacci(4), 3);
}

TEST_F(UtilityTests, fibonacci_50) {
  EXPECT_EQ(unit_under_test_->fibonacci(50), 12586269025);
}

TEST_F(UtilityTests, fibonacci_51) {
  EXPECT_EQ(unit_under_test_->fibonacci(51), 0);
}

TEST_F(UtilityTests, get_fibonacci_max_value) {
  EXPECT_EQ(unit_under_test_->get_max_fibonacci_value(), 51);
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
