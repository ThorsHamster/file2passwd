
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include <string>

class file2passwd {

private:
	std::string md5_from_file;
	unsigned long get_size_by_fd(int fd);

public:
	std::string get_md5_hash_from_file(const char* file_path);
    std::string generate_passwd_from_file(const char* file_path, int passwd_length);


};

#endif /* SRC_FILE2PASSWD_HPP_ */
