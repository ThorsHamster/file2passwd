
#ifndef SRC_UTILITIES_HPP_
#define SRC_UTILITIES_HPP_

#include <string>

/// @brief Maximum allowed value for the fibonacci function used here.
#define MAX_FIBONACCI_VALUE 51

/// @file
/// @brief This file contains some helper functions.

/**  @brief Checks if a file exists

     @param[in]      argv_file_path      Absolute path to File
     @return         True if file exists, False if not.
  */
auto file_exists(std::string argv_file_path) -> bool;

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
auto fibonacci(uint64_t number) -> uint64_t;

#endif /* SRC_UTILITIES_HPP_ */
