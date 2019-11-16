
#include "main.hpp"
#include "file2passwd.hpp"
#include "utilities.hpp"
#include <iostream>
#include <fstream>
#include <string.h>
#include <gsl/gsl>

int main(int argc, const char *argv[])
{
  auto args = gsl::multi_span<const char*>(argv, argc);

  if (argc != 2)
    {
      std::cout << "Please specify a File. \n";
      return 1;
    }

  std::string file_path = args[1];

  if (!file_exists(file_path))
    {
      std::cout << "Not a valid File. \n";
      return 1;
    }

  file2passwd fpo(file_path);

  std::string passwd = fpo.get_passwd();
  std::cout << "password: '" << passwd << "'\n";

  return 0;
}
