#ifndef SRC_FILEREADER_INTERFACE_HPP_
#define SRC_FILEREADER_INTERFACE_HPP_

#include <string.h>

#include <fstream>
#include <iostream>
#include <limits>

namespace filereader {

class FileReaderInterface {
 public:
  explicit FileReaderInterface(){};
  virtual ~FileReaderInterface() = default;

  /**  @brief Checks if a file exists

     @param[in]      argv_file_path      Absolute path to File
     @return         True if file exists, False if not.
  */
  virtual auto file_exists(std::string argv_file_path) -> bool = 0;
  virtual auto get_file_size(std::string file_path_) -> std::streamsize = 0;
  virtual auto get_file_buffer(std::string file_path_, std::streamsize file_size, char *file_buffer) -> void = 0;

 protected:
  static constexpr int MAXIMUM_FILE_LENGTH = 1000000;
};

}  // namespace filereader

#endif /* SRC_FILEREADER_INTERFACE_HPP_ */
