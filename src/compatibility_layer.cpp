#include "compatibility_layer.hpp"

#include <gsl/gsl>

namespace compatlayer {

/// @file
/// @brief This file contains a internal helper Class to be C++ compliant.

auto CompatibilityLayer::encrypt(const std::string &key, const std::string &iv, const std::string &plaintext) -> std::string {
  /* A 256 bit key */
  std::vector<unsigned char> key_uchar = string_to_unsigned_char(key);
  unsigned char *key_ = key_uchar.data();

  /* A 128 bit IV */
  std::vector<unsigned char> uv_uchar = string_to_unsigned_char(iv);
  unsigned char *iv_ = uv_uchar.data();

  /* Plaintext to be encrypted */
  std::vector<unsigned char> plaintext_uchar = string_to_unsigned_char(plaintext);
  unsigned char *plaintext_ = plaintext_uchar.data();

  /* Encrypt the plaintext */
  return open_ssl_->encrypt(plaintext_, key_, iv_);
}

auto CompatibilityLayer::string_to_unsigned_char(std::string const &str) -> std::vector<unsigned char> {
  auto vector_uchar = std::vector<unsigned char>(str.data(), str.data() + str.length());
  return std::move(vector_uchar);
}

}  // namespace compatlayer