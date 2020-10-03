#ifndef MOCK_UTILITIES_HPP_
#define MOCK_UTILITIES_HPP_

#include <gmock/gmock.h>

#include "utilities_interface.hpp"

namespace utilities {

class MockUtilities : public UtilitiesInterface {
 public:
  MockUtilities() : UtilitiesInterface() {}
  MOCK_METHOD(bool, file_exists, (std::string argv_file_path), (override));
  MOCK_METHOD(uint64_t, fibonacci, (uint64_t number), (override));
  MOCK_METHOD(uint64_t, get_max_fibonacci_value, (), (override));
  MOCK_METHOD(std::streamsize, get_file_size, (std::string file_path_), (override));
  MOCK_METHOD(void, get_file_buffer, (std::string file_path_, std::streamsize file_size, char *file_buffer), (override));
};

}  // namespace utilities

#endif