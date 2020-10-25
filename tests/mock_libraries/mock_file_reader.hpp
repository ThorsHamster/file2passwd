#ifndef MOCK_FILE_READER_HPP_
#define MOCK_FILE_READER_HPP_

#include <gmock/gmock.h>

#include "file_reader_interface.hpp"

namespace filereader {

class MockFileReader : public FileReaderInterface {
 public:
  MockFileReader(const std::string &file_path) : FileReaderInterface("") {}
  MOCK_METHOD(bool, file_exists, (), (override));
  MOCK_METHOD(std::vector<char>, get_file_buffer, (), (override));
  MOCK_METHOD(std::int64_t, get_file_size, (), (override));
};

}  // namespace filereader

#endif