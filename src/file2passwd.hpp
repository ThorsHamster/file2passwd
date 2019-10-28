
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include "compatibility_layer.hpp"
#include <string>

class file2passwd {

private:
	std::string file_path;

public:
	std::string md5_from_file;

	std::string get_md5_hash_from_file(void);
    std::string generate_passwd_from_file(int passwd_length);
    uint64_t fibonacci(uint64_t number);

    file2passwd(std::string file_path);
};

#endif /* SRC_FILE2PASSWD_HPP_ */
