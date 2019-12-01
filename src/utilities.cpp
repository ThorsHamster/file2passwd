#include "utilities.hpp"
#include <iostream>
#include <fstream>
#include <string.h>

bool file_exists(std::string argv_file_path)
{
  std::ifstream f(argv_file_path);
  return (!f.good())? false : true;
}

uint64_t fibonacci(uint64_t number)
{
  if (number == 0 or number >= MAX_FIBONACCI_VALUE)
    {
      return 0;
    }

  uint64_t f_n_2 = 1;
  uint64_t f_n_1 = 0;
  uint64_t f_n = 0;
  // f_n = f_(n-1) + f_(n-2) for n>=3
  for (int i=1; i<=number; i++)
    {
      f_n = f_n_1 + f_n_2;
      f_n_2 = f_n_1;
      f_n_1 = f_n;
    }

  return f_n;
}
