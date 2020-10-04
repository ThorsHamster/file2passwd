#include "file_reader.hpp"

namespace filereader {

auto FileReader::file_exists(void) -> bool {
  std::ifstream f(file_path_);
  return (f.good()) ? true : false;
}

auto FileReader::get_file_size(void) -> std::streamsize {
  std::ifstream file;
  file.open(file_path_, std::ios_base::in);
  file.ignore(std::numeric_limits<std::streamsize>::max());
  std::streamsize file_size = file.gcount();
  file.close();

  return file_size;
}

void FileReader::get_file_buffer(std::streamsize file_size, char *file_buffer) {
  if (file_size > 0 or file_size <= MAXIMUM_FILE_LENGTH) {
    std::ifstream file;
    file.open(file_path_, std::ios_base::in | std::ios_base::binary);
    file.seekg(0, std::ios_base::beg);
    file.read(file_buffer, file_size);
    file.close();
  }
}

}  // namespace filereader