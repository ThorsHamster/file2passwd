
#include "file2passwd.hpp"
#include <sys/mman.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>

#include <openssl/md5.h>
#include <gsl/gsl>

std::streamsize file2passwd::get_file_size(std::string file_path)
{
	std::ifstream file;
	file.open(file_path, std::ios_base::in);
	file.ignore(std::numeric_limits<std::streamsize>::max());
	std::streamsize file_size = file.gcount();
	file.close();

	return file_size;
}

void file2passwd::get_file_buffer(std::string file_path, std::streamsize file_size, char* file_buffer)
{
	std::ifstream file;
	file.open(file_path, std::ios_base::in | std::ios_base::binary);
	file.seekg( 0, std::ios_base::beg);
	file.read(file_buffer, file_size);
	file.close();
}

std::string file2passwd::get_md5_hash_from_file(std::string file_path)
{
	unsigned char result[MD5_DIGEST_LENGTH];

	std::streamsize file_size = get_file_size(file_path);
	char file_buffer[file_size];
	get_file_buffer(file_path, file_size, file_buffer);

	MD5((unsigned char*) file_buffer, file_size, (unsigned char*)result);
	munmap((char*)file_buffer, file_size);

	std::stringstream ss;
	ss << std::hex << std::setfill('0');
	for(int i = 0; i < MD5_DIGEST_LENGTH; i++)
	{
	    ss << std::setw(2) << static_cast<unsigned>(gsl::at(result, i));
	}
	md5_from_file = ss.str();

	return md5_from_file;
}
