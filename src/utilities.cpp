#include <iostream>
#include <fstream>
#include <string.h>


bool file_exists(std::string argv_file_path)
{
  std::ifstream f(argv_file_path);
  if (!f.good())
    {
      return false;
    }
  else
    {
      return true;
    }
}
