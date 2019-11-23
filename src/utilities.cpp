#include "utilities.hpp"
#include <iostream>
#include <fstream>
#include <string.h>

/// @file
/// @brief This file contains some helper functions.

/**  @brief Checks if a file exists

     @param[in]      argv_file_path      Absolute path to File
     @return         True if file exists, False if not.
  */
bool file_exists(std::string argv_file_path)
{
  std::ifstream f(argv_file_path);
  return (!f.good())? false : true;
}

/**  @brief Calculates fibonacci numbers

     @param[in]      number      Position in Fibonacci Series
     @return         Fibonacci Number at position \a number

     @note: Allowed range of \a number from 0 to 50.

 * <TABLE>
 * <TR><TD>number</TD><TD>fibonacci(number)</TD></TR>
 * <TR><TD>0</TD><TD>0</TD></TR>
 * <TR><TD>1</TD><TD>1</TD></TR>
 * <TR><TD>2</TD><TD>1</TD></TR>
 * <TR><TD>3</TD><TD>2</TD></TR>
 * <TR><TD>4</TD><TD>3</TD></TR>
 * <TR><TD>..</TD><TD>..</TD></TR>
 * <TR><TD>50</TD><TD>12586269025</TD></TR>
 * <TR><TD>51</TD><TD>invalid, returns 0</TD></TR>
 * </TABLE>
 */
uint64_t fibonacci(uint64_t number)
{
  if (number <= 0 or number >= MAX_FIBONACCI_VALUE)
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
