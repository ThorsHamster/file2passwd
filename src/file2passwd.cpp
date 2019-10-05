
#include "file2passwd.hpp"
#include <sys/mman.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

#include <openssl/md5.h>
#include <gsl/gsl>

std::string file2passwd::char_array_to_hex_string(unsigned char* result)
{
	// convert unsigned char array to string
	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
	    ss << std::setw(2) << static_cast<unsigned>(result[i]);
	}
	std::string result_string = ss.str();
	return result_string;
}

std::string file2passwd::get_md5_hash_from_file(const char* file_path)
{

	unsigned char result[MD5_DIGEST_LENGTH];

	std::ifstream file;
	file.open(file_path, std::ios_base::in | std::ios_base::binary);
	file.ignore(std::numeric_limits<std::streamsize>::max());
	std::streamsize file_size = file.gcount();
	file.clear();   //  Since ignore will have set eof.
	file.seekg( 0, std::ios_base::beg);

	char file_buffer[file_size];
	file.read(file_buffer, file_size);
	file.close();

	MD5((unsigned char*) file_buffer, file_size, (unsigned char*)result);
	munmap((char*)file_buffer, file_size);

	md5_from_file = char_array_to_hex_string((unsigned char*)result);

	return md5_from_file;
}
