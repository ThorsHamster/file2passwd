
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include <string>

class file2passwd {

private:
	std::string file_path;

	std::streamsize get_file_size(void);
	void get_file_buffer(std::streamsize file_size, char* file_buffer);
	std::string convert_uchar_ptr_to_hex_string(unsigned char* result);

public:
	std::string md5_from_file;

	std::string get_md5_hash_from_file(void);
    std::string generate_passwd_from_file(int passwd_length);

    file2passwd(std::string file_path);
};

#endif /* SRC_FILE2PASSWD_HPP_ */
