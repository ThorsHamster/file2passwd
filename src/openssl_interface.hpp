#ifndef SRC_OPENSSL_INTERFACE_HPP_
#define SRC_OPENSSL_INTERFACE_HPP_

#include <string.h>

#include <vector>

namespace openssl {

class OpenSSLInterface {
 public:
  explicit OpenSSLInterface() {}
  virtual ~OpenSSLInterface() = default;

  virtual auto get_md5_hash_from_file(std::vector<char> file_buffer) -> std::string = 0;
  virtual auto encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                       unsigned char *iv) -> std::string = 0;
};

}  // namespace openssl

#endif
