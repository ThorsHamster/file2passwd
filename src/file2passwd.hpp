
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include "compatibility_layer.hpp"
#include <string>
#include <vector>

class file2passwd {
public:

  std::string get_md5_hash_from_file(void);
  std::string get_passwd(void);

  file2passwd(std::string argv_file_path) : file_path(argv_file_path), compat(argv_file_path) {}

private:
  std::string file_path;
  compat_layer compat;
  std::string md5_from_file;

  std::string get_fibonacci_char_vector(void);
  std::string generate_passwd_from_file(int passwd_length);

  void handleErrors(void);
  int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
	      unsigned char *iv, unsigned char *ciphertext);
  std::string get_key(void);
  std::string get_iv(void);
};

#endif /* SRC_FILE2PASSWD_HPP_ */
