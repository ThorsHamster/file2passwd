#include "compatibility_layer.hpp"

#include <gsl/gsl>

namespace compatlayer {

/// @file
/// @brief This file contains a internal helper Class to be C++ compliant.

auto CompatibilityLayer::init(std::string file_path,
                              std::unique_ptr<utilities::UtilitiesInterface> utilities,
                              std::unique_ptr<filereader::FileReader> file_reader) -> void {
  file_path_ = file_path;
  utilities_ = std::move(utilities);
  file_reader_ = std::move(file_reader);
}

auto CompatibilityLayer::get_md5_hash_from_file(void) -> std::string {
  if (!file_reader_->file_exists(file_path_)) {
    throw FileDoesNotExistException();
  }

  auto result = std::make_unique<unsigned char[]>(MD5_DIGEST_LENGTH);

  std::streamsize file_size = file_reader_->get_file_size(file_path_);
  char file_buffer[file_size];                                      //NOLINT(cppcoreguidelines-avoid-c-arrays)
  file_reader_->get_file_buffer(file_path_, file_size, file_buffer);  //NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

  MD5((unsigned char *)file_buffer, file_size, result.get());  //NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
  munmap((char *)file_buffer, file_size);

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
  openssl_encrypt(plaintext_, strlen((char *)plaintext_), key_, iv_, ciphertext_);

  return convert_uchar_ptr_to_hex_string(ciphertext_);
}

auto CompatibilityLayer::openssl_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
                                         unsigned char *iv, unsigned char *ciphertext) -> int {
  EVP_CIPHER_CTX *ctx;

  int len;

  int ciphertext_len;

  /* Create and initialise the context */
  if (!(ctx = EVP_CIPHER_CTX_new()))
    handleErrors();

  /*
   * Initialise the encryption operation. IMPORTANT - ensure you use a key
   * and IV size appropriate for your cipher
   * In this example we are using 256 bit AES (i.e. a 256 bit key). The
   * IV size for *most* modes is the same as the block size. For AES this
   * is 128 bits
   */
  if (1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, key, iv))
    handleErrors();

  /*
   * Provide the message to be encrypted, and obtain the encrypted output.
   * EVP_EncryptUpdate can be called multiple times if necessary
   */
  if (1 != EVP_EncryptUpdate(ctx, ciphertext, &len, plaintext, plaintext_len))
    handleErrors();
  ciphertext_len = len;

  /*
   * Finalise the encryption. Further ciphertext bytes may be written at
   * this stage.
   */
  if (1 != EVP_EncryptFinal_ex(ctx, ciphertext + len, &len))
    handleErrors();
  ciphertext_len += len;

  /* Clean up */
  EVP_CIPHER_CTX_free(ctx);

  return ciphertext_len;
}

void CompatibilityLayer::handleErrors(void) {
  ERR_print_errors_fp(stderr);
  abort();
}

auto CompatibilityLayer::string_to_unsigned_char(std::string const &str) -> std::vector<unsigned char> {
  auto vector_uchar = std::vector<unsigned char>(str.data(), str.data() + str.length());
  return std::move(vector_uchar);
}

}  // namespace compatlayer