#ifndef SRC_UTILITIES_INTERFACE_HPP_
#define SRC_UTILITIES_INTERFACE_HPP_

#include <memory>
#include <string>
#include <vector>

/// @file
/// @brief This file contains some helper functions.

namespace utilities {

class UtilitiesInterface {
 public:
  explicit UtilitiesInterface(){};
  virtual ~UtilitiesInterface() = default;

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
  virtual auto fibonacci(std::uint64_t number) -> std::uint64_t = 0;

  virtual auto get_max_fibonacci_value(void) -> std::uint64_t = 0;

 protected:
  /// @brief Maximum allowed value for the fibonacci function used here.
  static constexpr int MAX_FIBONACCI_VALUE = 51;
};

}  // namespace utilities

#endif /* SRC_UTILITIES_HPP_ */
