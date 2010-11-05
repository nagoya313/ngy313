#pragma once
#include <cstring>
#include <string>
#include <boost/filesystem/path.hpp>

namespace ngy313 {
class string_piece {
 public:
  typedef std::size_t size_type;

  string_piece() : str_(nullptr), length_(0) {}

  string_piece(const char * const str)
    : str_(str), length_(str_ ? std::strlen(str_) : 0) {}

  string_piece(const char * const str, const size_type length)
    : str_(str), length_(length) {}

  string_piece(const std::string &str) 
    : str_(str.c_str()), length_(str.length()) {}

  string_piece(const boost::filesystem::path &str) 
    : str_(str.string().c_str()), length_(str.string().length()) {}

  const char *c_str() const {
    return str_;
  }

  size_type length() const {
    return length_;
  }

  bool empty() const {
    return !length_;
  }

  std::string string() const {
    return std::string(!empty() ? c_str() : "", length());
  }

 private:
  const char *str_;
  size_type length_;
};
}