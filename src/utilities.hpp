#ifndef SRC_UTILITIES_HPP_
#define SRC_UTILITIES_HPP_

#include <string.h>

#include <fstream>
#include <iostream>

#include "utilities_interface.hpp"

namespace utilities {

class Utilities : public UtilitiesInterface {
 public:
  explicit Utilities() : UtilitiesInterface(){};
  ~Utilities() = default;

  auto file_exists(std::string argv_file_path) -> bool override;
  auto fibonacci(uint64_t number) -> uint64_t override;
  auto get_max_fibonacci_value(void) -> uint64_t override;
};

}  // namespace utilities

#endif /* SRC_UTILITIES_HPP_ */
