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
  virtual auto encrypt(std::string plaintext, std::string key, std::string iv) -> std::string = 0;
};

}  // namespace openssl

#endif
