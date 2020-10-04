
#include "file2passwd_interface.hpp"

namespace file2passwd {

File2Passwd::File2Passwd(const std::string &path_to_file) {
  file2passwd_ = std::make_unique<file2passwd::File2PasswdInternal>();
  std::unique_ptr<utilities::UtilitiesInterface> utilities_ = std::make_unique<utilities::Utilities>();
  std::unique_ptr<compatlayer::CompatibilityLayerInterface> compat_ = std::make_unique<compatlayer::CompatibilityLayer>();
  std::unique_ptr<filereader::FileReader> file_reader_ = std::make_unique<filereader::FileReader>();

  compat_->init(path_to_file, std::make_unique<utilities::Utilities>(), std::make_unique<filereader::FileReader>());
  file2passwd_->init(path_to_file, std::move(compat_), std::move(utilities_), std::move(file_reader_));
}

auto File2Passwd::get_passwd(void) -> std::string {
  return file2passwd_->get_passwd();
}

auto File2Passwd::get_md5_hash(void) -> std::string {
  return file2passwd_->get_md5_hash();
}

}  // namespace file2passwd