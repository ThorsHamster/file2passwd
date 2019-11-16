
#ifndef SRC_COMPATLAYER_HPP_
#define SRC_COMPATLAYER_HPP_

#include <string>

class compat_layer {
public:
  std::string md5_from_file;

  std::string get_md5_hash_from_file(void);
  std::string convert_uchar_ptr_to_hex_string(unsigned char* result);

  compat_layer(std::string file_path);

private:
  std::string file_path;

  std::streamsize get_file_size(void);
  void get_file_buffer(std::streamsize file_size, char* file_buffer);
};

#endif /* SRC_COMPATLAYER_HPP_ */
