
#include "file2passwd.hpp"
#include "compatibility_layer.hpp"
#include "utilities.hpp"

file2passwd::file2passwd(std::string argv_file_path)
{
	file_path = argv_file_path;
}

std::string file2passwd::get_md5_hash_from_file(void)
{
	if(!file_exists(file_path))
	{
		return "";
	}

	compat_layer compat(file_path);
	md5_from_file = compat.get_md5_hash_from_file();
	return md5_from_file;
}

uint64_t file2passwd::fibonacci(uint64_t number)
{
	const uint64_t MAX_FIBONACCI_VALUE = 51;
	if(number <= 0 or number >= MAX_FIBONACCI_VALUE)
	{
		return 0;
	}

	uint64_t f_n_2 = 1;
	uint64_t f_n_1 = 0;
	uint64_t f_n = 0;
	// f_n = f_(n-1) + f_(n-2) for n>=3
	for(int i=1; i<=number; i++)
	{
		f_n = f_n_1 + f_n_2;
		f_n_2 = f_n_1;
		f_n_1 = f_n;
	}

	return f_n;
}
