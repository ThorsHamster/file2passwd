#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include "compatibility_layer.hpp"
#include "file_reader.hpp"
#include "openssl.hpp"
#include "utilities.hpp"

namespace file2passwd {

class File2PasswdInternal {
 public:
  auto get_md5_hash(void) -> std::string;
  auto get_passwd(void) -> std::string;

  explicit File2PasswdInternal(std::unique_ptr<compatlayer::CompatibilityLayerInterface> compat,
                               std::unique_ptr<utilities::UtilitiesInterface> utilities,
                               std::unique_ptr<filereader::FileReaderInterface> file_reader,
                               std::unique_ptr<openssl::OpenSSLInterface> open_ssl) : compat_(std::move(compat)),
                                                                                      utilities_(std::move(utilities)),
                                                                                      file_reader_(std::move(file_reader)),
                                                                                      open_ssl_(std::move(open_ssl)){};

 private:
  std::string md5_hash_of_file;
  std::unique_ptr<compatlayer::CompatibilityLayerInterface> compat_;
  std::unique_ptr<utilities::UtilitiesInterface> utilities_;
  std::unique_ptr<filereader::FileReaderInterface> file_reader_;
  std::unique_ptr<openssl::OpenSSLInterface> open_ssl_;

  void check_for_prerequisites(void);

  auto get_key(void) -> std::string;
  auto get_iv(void) -> std::string;
  auto get_fibonacci_string(void) -> std::string;
  auto get_fibonacci_vector_of_filelength(std::ifstream::pos_type length_of_file) -> std::vector<uint64_t>;
  auto pick_chars_from_file(std::vector<uint64_t> fibonacci_numbers, std::vector<char> &file_buffer) -> std::string;
};

}  // namespace file2passwd

#endif /* SRC_FILE2PASSWD_HPP_ */
