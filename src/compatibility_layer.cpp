#include "compatibility_layer.hpp"
#include "utilities.hpp"
#include <sys/mman.h>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string.h>
#include <openssl/md5.h>
#include <gsl/gsl>

/// @file
/// @brief This file contains a internal helper Class to be C++ compliant.

CompatibilityLayer::CompatibilityLayer(std::string path_to_file)
{
  file_path = path_to_file;
}

std::streamsize CompatibilityLayer::get_file_size(void)
{
  std::ifstream file;
  file.open(file_path, std::ios_base::in);
  file.ignore(std::numeric_limits<std::streamsize>::max());
  std::streamsize file_size = file.gcount();
  file.close();

  return file_size;
}

void CompatibilityLayer::get_file_buffer(std::streamsize file_size, char* file_buffer)
{
  std::ifstream file;
  file.open(file_path, std::ios_base::in | std::ios_base::binary);
  file.seekg( 0, std::ios_base::beg);
  file.read(file_buffer, file_size);
  file.close();
}

std::string CompatibilityLayer::convert_uchar_ptr_to_hex_string(unsigned char* result)
{
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (int i = 0; i < MD5_DIGEST_LENGTH; i++)
    {
      ss << std::setw(2) << static_cast<unsigned>(result[i]); //NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
    }
  return ss.str();
}

std::string CompatibilityLayer::get_md5_hash_from_file(void)
{
  if (!file_exists(file_path))
    {
      return "";
    }

  unsigned char* result = new unsigned char[MD5_DIGEST_LENGTH]; //NOLINT(cppcoreguidelines-owning-memory)

  std::streamsize file_size = get_file_size();
  char file_buffer[file_size]; //NOLINT(cppcoreguidelines-avoid-c-arrays)
  get_file_buffer(file_size, file_buffer); //NOLINT(cppcoreguidelines-pro-bounds-array-to-pointer-decay)

  MD5((unsigned char*) file_buffer, file_size, result); //NOLINT(cppcoreguidelines-pro-type-cstyle-cast)
  munmap((char*)file_buffer, file_size);

  md5_from_file = convert_uchar_ptr_to_hex_string(result);

  delete result; //NOLINT(cppcoreguidelines-owning-memory)
  return md5_from_file;
}
