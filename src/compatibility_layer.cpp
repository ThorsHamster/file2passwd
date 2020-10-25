#include "compatibility_layer.hpp"

#include <gsl/gsl>

namespace compatlayer {

/// @file
/// @brief This file contains a internal helper Class to be C++ compliant.

auto CompatibilityLayer::get_md5_hash_from_file(void) -> std::string {
  std::vector<char> file_buffer;
  file_buffer = file_reader_->get_file_buffer();

  md5_from_file = open_ssl_->get_md5_hash_from_file(file_buffer);

  return md5_from_file;
}

auto CompatibilityLayer::encrypt(const std::string &key, const std::string &iv, const std::string &plaintext) -> std::string {
  /* A 256 bit key */
  std::vector<unsigned char> key_uchar = string_to_unsigned_char(key);
  unsigned char *key_ = key_uchar.data();

  /* A 128 bit IV */
  std::vector<unsigned char> uv_uchar = string_to_unsigned_char(iv);
  unsigned char *iv_ = uv_uchar.data();

  /* Message to be encrypted */
  std::vector<unsigned char> msg_uchar = string_to_unsigned_char(plaintext);
  unsigned char *plaintext_ = msg_uchar.data();
  /*
   * Buffer for ciphertext. Ensure the buffer is long enough for the
   * ciphertext which may be longer than the plaintext, depending on the
   * algorithm and mode.
   */
  unsigned char ciphertext_[128];

  /* Encrypt the plaintext */
  return open_ssl_->encrypt(plaintext_, strlen((char *)plaintext_), key_, iv_, ciphertext_);
}

auto CompatibilityLayer::string_to_unsigned_char(std::string const &str) -> std::vector<unsigned char> {
  auto vector_uchar = std::vector<unsigned char>(str.data(), str.data() + str.length());
  return std::move(vector_uchar);
}

}  // namespace compatlayer