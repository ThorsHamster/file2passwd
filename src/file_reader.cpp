#include "file_reader.hpp"

#include <iterator>

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

auto FileReader::get_file_buffer(std::streamsize file_size) -> std::vector<char> {
  if (file_size > 0 or file_size <= MAXIMUM_FILE_LENGTH) {
    std::ifstream file(file_path_, std::ios::binary);

    return std::vector<char>((std::istreambuf_iterator<char>(file)),
                             std::istreambuf_iterator<char>());
  } else {
    return std::vector<char>();
  }
}

}  // namespace filereader