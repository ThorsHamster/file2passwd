#ifndef MOCK_FILE_READER_HPP_
#define MOCK_FILE_READER_HPP_

#include <gmock/gmock.h>

#include "file_reader_interface.hpp"

namespace filereader {

class MockFileReader : public FileReaderInterface {
 public:
  MockFileReader(std::string file_path) : FileReaderInterface("") {}
  MOCK_METHOD(bool, file_exists, (), (override));
  MOCK_METHOD(std::streamsize, get_file_size, (), (override));
  MOCK_METHOD(void, get_file_buffer, (std::streamsize file_size, char *file_buffer), (override));
};

}  // namespace filereader

#endif