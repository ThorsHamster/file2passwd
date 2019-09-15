
#ifndef SRC_FILE2PASSWD_HPP_
#define SRC_FILE2PASSWD_HPP_

#include <string>

class file2passwd {

private:
	std::string md5;


public:
    std::string generate_passwd_from_file (std::string filename, int passwd_length);

};

#endif /* SRC_FILE2PASSWD_HPP_ */
