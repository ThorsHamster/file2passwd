
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include <string>

class file2passwd {

private:


public:
	std::string md5_from_file;
	std::string get_md5_hash_from_file(std::string file_path);
    std::string generate_passwd_from_file(std::string file_path, int passwd_length);

};

#endif /* SRC_FILE2PASSWD_HPP_ */
