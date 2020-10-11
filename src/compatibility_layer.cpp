#include "compatibility_layer.hpp"

#include <gsl/gsl>

namespace compatlayer {

/// @file
/// @brief This file contains a internal helper Class to be C++ compliant.

auto CompatibilityLayer::init(std::unique_ptr<utilities::UtilitiesInterface> utilities,
                              std::unique_ptr<filereader::FileReaderInterface> file_reader,
                              std::unique_ptr<openssl::OpenSSLInterface> open_ssl) -> void {
  utilities_ = std::move(utilities);
  file_reader_ = std::move(file_reader);
  open_ssl_ = std::move(open_ssl);
}

auto CompatibilityLayer::get_md5_hash_from_file(void) -> std::string {
  if (!file_reader_->file_exists()) {
    throw FileDoesNotExistException();
  }

  auto result = std::make_unique<unsigned char[]>(MD5_DIGEST_LENGTH);

  std::vector<char> file_buffer;
  file_buffer = file_reader_->get_file_buffer();

  MD5((unsigned char *)file_buffer.data(), file_buffer.size(), result.get());
  md5_from_file = convert_uchar_ptr_to_hex_string(result.get());

  return md5_from_file;
}

auto CompatibilityLayer::convert_uchar_ptr_to_hex_string(unsigned char *result) -> std::string {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++) {
    ss << std::setw(2) << static_cast<unsigned>(result[i]);  //NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
  }
  return ss.str();
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
  open_ssl_->encrypt(plaintext_, strlen((char *)plaintext_), key_, iv_, ciphertext_);

  return convert_uchar_ptr_to_hex_string(ciphertext_);
}

auto CompatibilityLayer::string_to_unsigned_char(std::string const &str) -> std::vector<unsigned char> {
  auto vector_uchar = std::vector<unsigned char>(str.data(), str.data() + str.length());
  return std::move(vector_uchar);
}

}  // namespace compatlayer