
#include "main.hpp"
#include "file2passwd.hpp"
#include <iostream>
#include <string.h>
#include <gsl/gsl>

int main(int argc, const char *argv[])
{
	auto args = gsl::multi_span<const char*>(argv, argc);

	if(argc != 2) {
		std::cout << "Please specify a File. \n";
		return 1;
	}

	file2passwd fpo;

	std::string result;
	std::string file_path = args[1];
	result = fpo.get_md5_hash_from_file(file_path);

	std::cout << result << "\n";
	std::cout << fpo.md5_from_file << "\n";

	return 0;
}
