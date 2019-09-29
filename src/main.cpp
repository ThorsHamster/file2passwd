
#include "main.hpp"
#include "file2passwd.hpp"
#include <iostream>
#include <string.h>

int main(int argc, char *argv[])
{
	if(argc != 2) {
		std::cout << "Please specify a File. \n";
		exit(-1);
	}

	file2passwd fpo;

	std::string result;
	result = fpo.get_md5_hash_from_file(argv[1]);

	std::cout << result << "\n";
	std::cout << fpo.md5_from_file << "\n";

	return 0;
}
