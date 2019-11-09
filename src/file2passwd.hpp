
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include "compatibility_layer.hpp"
#include <string>
#include <vector>

class file2passwd {
private:
	std::string file_path;
	void handleErrors(void);
	int encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key,
	            unsigned char *iv, unsigned char *ciphertext);
	std::string get_key(void);
	std::string get_iv(void);

public:
	std::string md5_from_file;

	std::string get_fibonacci_char_vector(void);
	std::string get_md5_hash_from_file(void);
    std::string generate_passwd_from_file(int passwd_length);
    uint64_t fibonacci(uint64_t number);
    std::string get_passwd(void);

    file2passwd(std::string file_path);
};

#endif /* SRC_FILE2PASSWD_HPP_ */
