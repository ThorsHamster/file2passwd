
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

TEST_F(ExceptionTests, FileDoesNotExistException_get_Exception_Message) {
  EXPECT_EQ(FileDoesNotExistException().what(), "File does not exist.");
}

TEST_F(ExceptionTests, FileIsEmpty_get_Exception_Message) {
  EXPECT_EQ(FileIsEmpty().what(), "File is empty.");
}

TEST_F(ExceptionTests, OpenSSLException_get_Exception_Message) {
  EXPECT_EQ(OpenSSLException().what(), "Failure with OpenSSL occured.");
}
}  // namespace

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
