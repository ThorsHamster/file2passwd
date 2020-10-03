#include "utilities.hpp"

namespace utilities {

auto Utilities::file_exists(std::string argv_file_path) -> bool {
  std::ifstream f(argv_file_path);
  return (f.good()) ? true : false;
}

auto Utilities::fibonacci(uint64_t number) -> uint64_t {
  if (number == 0 or number >= MAX_FIBONACCI_VALUE) {
    return 0;
  }

  uint64_t f_n_2 = 1;
  uint64_t f_n_1 = 0;
  uint64_t f_n = 0;
  // f_n = f_(n-1) + f_(n-2) for n>=3
  for (int i = 1; i <= number; i++) {
    f_n = f_n_1 + f_n_2;
    f_n_2 = f_n_1;
    f_n_1 = f_n;
  }

  return f_n;
}

auto Utilities::get_max_fibonacci_value(void) -> uint64_t {
  return MAX_FIBONACCI_VALUE;
}

auto Utilities::get_file_size(std::string file_path_) -> std::streamsize {
  std::ifstream file;
  file.open(file_path_, std::ios_base::in);
  file.ignore(std::numeric_limits<std::streamsize>::max());
  std::streamsize file_size = file.gcount();
  file.close();

  return file_size;
}

void Utilities::get_file_buffer(std::string file_path_, std::streamsize file_size, char *file_buffer) {
  if (file_size > 0 or file_size <= MAXIMUM_FILE_LENGTH) {
    std::ifstream file;
    file.open(file_path_, std::ios_base::in | std::ios_base::binary);
    file.seekg(0, std::ios_base::beg);
    file.read(file_buffer, file_size);
    file.close();
  }
}

}  // namespace utilities