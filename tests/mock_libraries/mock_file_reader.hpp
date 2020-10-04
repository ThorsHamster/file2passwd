#ifndef MOCK_UTILITIES_HPP_
#define MOCK_UTILITIES_HPP_

#include <gmock/gmock.h>

#include "file_reader_interface.hpp"

namespace filereader {

class MockFileReader : public FileReaderInterface {
 public:
  MockFileReader() : FileReaderInterface() {}
  MOCK_METHOD(bool, file_exists, (std::string argv_file_path), (override));
  MOCK_METHOD(std::streamsize, get_file_size, (std::string file_path_), (override));
  MOCK_METHOD(void, get_file_buffer, (std::string file_path_, std::streamsize file_size, char *file_buffer), (override));
};

}  // namespace filereader

#endif