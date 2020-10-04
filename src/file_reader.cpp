#include "file_reader.hpp"

namespace filereader {

auto FileReader::file_exists(std::string argv_file_path) -> bool {
  std::ifstream f(argv_file_path);
  return (f.good()) ? true : false;
}

auto FileReader::get_file_size(std::string file_path_) -> std::streamsize {
  std::ifstream file;
  file.open(file_path_, std::ios_base::in);
  file.ignore(std::numeric_limits<std::streamsize>::max());
  std::streamsize file_size = file.gcount();
  file.close();

  return file_size;
}

void FileReader::get_file_buffer(std::string file_path_, std::streamsize file_size, char *file_buffer) {
  if (file_size > 0 or file_size <= MAXIMUM_FILE_LENGTH) {
    std::ifstream file;
    file.open(file_path_, std::ios_base::in | std::ios_base::binary);
    file.seekg(0, std::ios_base::beg);
    file.read(file_buffer, file_size);
    file.close();
  }
}

}  // namespace filereader