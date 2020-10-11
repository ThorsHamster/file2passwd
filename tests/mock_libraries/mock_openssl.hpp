#ifndef MOCK_OPENSSL_HPP_
#define MOCK_OPENSSL_HPP_

#include <gmock/gmock.h>

#include "openssl_interface.hpp"

namespace openssl {

class MockOpenSSL : public OpenSSLInterface {
 public:
  MockOpenSSL() : OpenSSLInterface() {}
  MOCK_METHOD(std::string, get_md5_hash_from_file, (std::vector<char> file_buffer), (override));
  MOCK_METHOD(int, encrypt, (unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext), (override));
};

}  // namespace openssl

#endif