#ifndef SRC_FILEREADER_HPP_
#define SRC_FILEREADER_HPP_

#include "file_reader_interface.hpp"

namespace filereader {

class FileReader : public FileReaderInterface {
 public:
  explicit FileReader() : FileReaderInterface(){};
  ~FileReader() = default;

  auto file_exists(std::string argv_file_path) -> bool override;
  auto get_file_size(std::string file_path_) -> std::streamsize override;
  auto get_file_buffer(std::string file_path_, std::streamsize file_size, char *file_buffer) -> void override;
};

}  // namespace filereader

#endif /* SRC_FILEREADER_HPP_ */
