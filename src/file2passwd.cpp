
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
