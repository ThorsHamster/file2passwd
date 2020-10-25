
#include <gmock/gmock.h>
#include <limits.h>
#include <string.h>

#include "openssl.hpp"

using ::testing::_;
using ::testing::NiceMock;
using ::testing::Return;

EVP_CIPHER_CTX* EVP_CIPHER_CTX_new_return;
int EVP_EncryptInit_ex_return;
int EVP_EncryptUpdate_return;
int EVP_EncryptFinal_ex_return;

namespace {
class OpenSSLTests : public ::testing::Test {
 protected:
  virtual void SetUp() {
  }

  virtual void ConfigureUnitUnderTest() {
    unit_under_test_ = std::make_unique<openssl::OpenSSL>();
  }

  std::unique_ptr<openssl::OpenSSL> unit_under_test_;
};

TEST_F(OpenSSLTests, get_md5_hash_from_file) {
  ConfigureUnitUnderTest();

  std::vector<char> file_buffer;

  //for testdata see md5.c
  EXPECT_EQ(unit_under_test_->get_md5_hash_from_file(file_buffer), "61626362626262626262626262626262");
}

TEST_F(OpenSSLTests, encrypt_happy_path) {
  ConfigureUnitUnderTest();

  unsigned char plaintext[] = {'p'};
  int plaintext_len = 3;
  unsigned char key[] = {'k'};
  unsigned char iv[] = {'v'};
  unsigned char ciphertext[] = {'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'};

  EVP_CIPHER_CTX* some_pointer;
  EVP_CIPHER_CTX_new_return = some_pointer;
  EVP_EncryptInit_ex_return = 1;
  EVP_EncryptUpdate_return = 1;
  EVP_EncryptFinal_ex_return = 1;

  EXPECT_EQ(unit_under_test_->encrypt(plaintext, plaintext_len, key, iv, ciphertext), "63636363636363636363636363636363");
}

TEST_F(OpenSSLTests, encrypt_false_return_EVP_CIPHER_CTX_new) {
  ConfigureUnitUnderTest();

  unsigned char plaintext[] = {'p'};
  int plaintext_len = 3;
  unsigned char key[] = {'k'};
  unsigned char iv[] = {'v'};
  unsigned char ciphertext[] = {'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'};

  EVP_CIPHER_CTX_new_return = NULL;
  EVP_EncryptInit_ex_return = 1;
  EVP_EncryptUpdate_return = 1;
  EVP_EncryptFinal_ex_return = 1;

  EXPECT_THROW(unit_under_test_->encrypt(plaintext, plaintext_len, key, iv, ciphertext), OpenSSLException);
}

TEST_F(OpenSSLTests, encrypt_false_return_EVP_EncryptInit_ex) {
  ConfigureUnitUnderTest();

  unsigned char plaintext[] = {'p'};
  int plaintext_len = 3;
  unsigned char key[] = {'k'};
  unsigned char iv[] = {'v'};
  unsigned char ciphertext[] = {'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'};

  EVP_CIPHER_CTX* some_pointer;
  EVP_CIPHER_CTX_new_return = some_pointer;
  EVP_EncryptInit_ex_return = 0;
  EVP_EncryptUpdate_return = 1;
  EVP_EncryptFinal_ex_return = 1;

  EXPECT_THROW(unit_under_test_->encrypt(plaintext, plaintext_len, key, iv, ciphertext), OpenSSLException);
}

TEST_F(OpenSSLTests, encrypt_false_return_EVP_EncryptUpdate) {
  ConfigureUnitUnderTest();

  unsigned char plaintext[] = {'p'};
  int plaintext_len = 3;
  unsigned char key[] = {'k'};
  unsigned char iv[] = {'v'};
  unsigned char ciphertext[] = {'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'};

  EVP_CIPHER_CTX* some_pointer;
  EVP_CIPHER_CTX_new_return = some_pointer;
  EVP_EncryptInit_ex_return = 1;
  EVP_EncryptUpdate_return = 0;
  EVP_EncryptFinal_ex_return = 1;

  EXPECT_THROW(unit_under_test_->encrypt(plaintext, plaintext_len, key, iv, ciphertext), OpenSSLException);
}

TEST_F(OpenSSLTests, encrypt_false_return_EVP_EncryptFinal_ex) {
  ConfigureUnitUnderTest();

  unsigned char plaintext[] = {'p'};
  int plaintext_len = 3;
  unsigned char key[] = {'k'};
  unsigned char iv[] = {'v'};
  unsigned char ciphertext[] = {'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c', 'c'};

  EVP_CIPHER_CTX* some_pointer;
  EVP_CIPHER_CTX_new_return = some_pointer;
  EVP_EncryptInit_ex_return = 1;
  EVP_EncryptUpdate_return = 1;
  EVP_EncryptFinal_ex_return = 0;

  EXPECT_THROW(unit_under_test_->encrypt(plaintext, plaintext_len, key, iv, ciphertext), OpenSSLException);
}
}  // namespace

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
