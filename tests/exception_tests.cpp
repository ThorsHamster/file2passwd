
#include <gmock/gmock.h>

#include "exception.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

namespace {

class ExceptionTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }
};

TEST_F(ExceptionTests, get_Exception_Message) {
  EXPECT_EQ(FileDoesNotExistException().what(), "File does not exist.");
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
