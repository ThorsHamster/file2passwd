
#include "file2passwd_interface.hpp"

namespace file2passwd {

File2Passwd::File2Passwd(const std::string &path_to_file) {
  file2passwd_ = std::make_unique<file2passwd::File2PasswdInternal>(path_to_file);
}

auto File2Passwd::get_passwd(void) -> std::string {
  return file2passwd_->get_passwd();
}

auto File2Passwd::get_md5_hash(void) -> std::string {
  return file2passwd_->get_md5_hash();
}

}  // namespace file2passwd