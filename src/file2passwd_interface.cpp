
#include "file2passwd_interface.hpp"

namespace file2passwd {

auto File2Passwd::get_passwd(void) -> std::string {
  return file2passwd_->get_passwd();
}

auto File2Passwd::get_md5_hash(void) -> std::string {
  return file2passwd_->get_md5_hash();
}

}  // namespace file2passwd