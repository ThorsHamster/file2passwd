
#include "main.hpp"

#include <string.h>

#include <fstream>
#include <gsl/gsl>
#include <iostream>

#include "file2passwd.hpp"
#include "utilities.hpp"

int main(int argc, const char *argv[]) {
  auto args = gsl::multi_span<const char *>(argv, argc);

  if (argc != 2) {
    std::cout << "Please specify a File. \n";
    return 1;
  }

  std::string file_path = args[1];

  File2Passwd fpo(file_path);

  std::string passwd = fpo.get_passwd();
  std::cout << "file: " << file_path << '\n';
  std::cout << "password: " << passwd << '\n';

  return 0;
}
