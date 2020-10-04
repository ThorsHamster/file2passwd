#ifndef SRC_FILEREADER_HPP_
#define SRC_FILEREADER_HPP_

#include "file_reader_interface.hpp"

namespace filereader {

class FileReader : public FileReaderInterface {
 public:
  explicit FileReader(std::string file_path) : FileReaderInterface(file_path){};
  ~FileReader() = default;

  auto file_exists(void) -> bool override;
  auto get_file_size(void) -> std::streamsize override;
  auto get_file_buffer(std::streamsize file_size) -> std::vector<char> override;
};

}  // namespace filereader

#endif /* SRC_FILEREADER_HPP_ */
