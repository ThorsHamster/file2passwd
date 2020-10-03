#ifndef MOCK_UTILITIES_HPP_
#define MOCK_UTILITIES_HPP_

#include <gmock/gmock.h>

#include "utilities_interface.hpp"

class MockUtilities : public utilities::UtilitiesInterface {
 public:
  MockUtilities() : utilities::UtilitiesInterface() {}
  MOCK_METHOD(bool, file_exists, (std::string argv_file_path), (override));
  MOCK_METHOD(uint64_t, fibonacci, (uint64_t number), (override));
  MOCK_METHOD(uint64_t, get_max_fibonacci_value, (), (override));
};

#endif