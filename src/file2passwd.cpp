
#include "file2passwd.hpp"
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <iostream>
#include <iomanip>
#include <string.h>

#include <openssl/md5.h>
#include "gsl/gsl-lite.hpp"

// Get the size of the file by its file descriptor
unsigned long file2passwd::get_size_by_fd(int fd) {
    struct stat statbuf {};
    if(fstat(fd, &statbuf) < 0)
    {
    	exit(-1);
    }
    return statbuf.st_size;
}

std::string file2passwd::get_md5_hash_from_file(const char* file_path) {

	unsigned char result[MD5_DIGEST_LENGTH];
	int file_descript;
	unsigned long file_size;
	unsigned char* file_buffer;

	file_descript = open(file_path, O_RDONLY);
	if(file_descript < 0) exit(-1);

	file_size = get_size_by_fd(file_descript);

	// get md5 from file via openssl/md5
	file_buffer = static_cast<unsigned char*>(mmap(0, file_size, PROT_READ, MAP_SHARED, file_descript, 0));
	MD5((unsigned char*) file_buffer, file_size, result);
	munmap(file_buffer, file_size);

	// convert unsigned char array to string
	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
	    ss << std::setw(2) << static_cast<unsigned>(gsl::at(result, i));
	}
	std::string result_string = ss.str();
	md5_from_file = result_string;

	return result_string;
}
