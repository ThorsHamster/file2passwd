
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include <string>

class file2passwd {

private:
    std::string generate_passwd_from_file(const std::string file_path, int passwd_length);


public:
    std::string get_md5_hash_from_file(const std::string file_path);
	std::string md5_from_file;

};

#endif /* SRC_FILE2PASSWD_HPP_ */
