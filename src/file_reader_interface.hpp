#ifndef SRC_FILEREADER_INTERFACE_HPP_
#define SRC_FILEREADER_INTERFACE_HPP_

#include <string.h>

#include <fstream>
#include <iostream>
#include <limits>

namespace filereader {

class FileReaderInterface {
 public:
  explicit FileReaderInterface(std::string file_path): file_path_(file_path){};
  virtual ~FileReaderInterface() = default;

  /**  @brief Checks if a file exists

     @param[in]      argv_file_path      Absolute path to File
     @return         True if file exists, False if not.
  */
  virtual auto file_exists(void) -> bool = 0;
  virtual auto get_file_size(void) -> std::streamsize = 0;
  virtual auto get_file_buffer(std::streamsize file_size, char *file_buffer) -> void = 0;

 protected:
  static constexpr int MAXIMUM_FILE_LENGTH = 1000000;
  std::string file_path_;
};

}  // namespace filereader

#endif /* SRC_FILEREADER_INTERFACE_HPP_ */
