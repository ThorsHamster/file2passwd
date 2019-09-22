
#include "file2passwd.hpp"
#include <fstream>
#include <iostream>
#include <openssl/md5.h>

std::string file2passwd::get_md5_hash_from_file(const std::string file_path) {

	std::ifstream File;
	File.open(file_path);

	if (!File) {
	    std::cout << "Unable to open File.";
	    exit(1);
	}
	File.close();

	std::cout << "Able to open File.";

	return file_path;
	//unsigned char * tmp_hash;
	//tmp_hash = MD5((const unsigned char*)filename, filename.length(), NULL);
	//return tmp_hash;
}
