
#include "main.hpp"
#include "file2passwd.hpp"
#include <iostream>
#include <string>

int main(int argc, char *argv[])
{

	if(argc != 2) {
	            printf("Please specify a File. \n");
	            exit(-1);
	}
	std::cout << "using file:\t%s\n" << argv[1];

	file2passwd fpo;

	fpo.get_md5_hash_from_file(argv[1]);

	return 0;
}
