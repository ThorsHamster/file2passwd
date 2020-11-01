
#ifndef SRC_OPENSSL_HPP_
#define SRC_OPENSSL_HPP_

#include <openssl/conf.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/md5.h>
#include <sys/mman.h>

#include <fstream>
#include <iomanip>
#include <iostream>

#include "exception.hpp"
#include "openssl_interface.hpp"

namespace openssl {

/**
* @class CompatibilityLayer
*
* @brief Internal helper Class to be C++ compliant.
*/
class OpenSSL : public OpenSSLInterface {
 public:
  explicit OpenSSL() {}

  auto get_md5_hash_from_file(std::vector<char> file_buffer) -> std::string override;
  auto encrypt(std::string plaintext, std::string key, std::string iv) -> std::string override;

 private:
  auto string_to_unsigned_char(std::string const &str) -> std::vector<unsigned char>;
  auto convert_uchar_ptr_to_hex_string(unsigned char *result) -> std::string;
  void handleErrors(void);
};

}  // namespace openssl

#endif /* SRC_OPENSSL_HPP_ */
