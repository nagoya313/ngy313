#pragma once
#include <cstring>
#include <string>
#include <boost/filesystem/path.hpp>

namespace ngy313 {
class string_piece {
 public:
  typedef std::size_t size_type;
  typedef char value_type;
  typedef const char *pointer;
  typedef const char &reference;
  typedef const char &const_reference;
  typedef std::ptrdiff_t difference_type;
  typedef const char *const_iterator;
  typedef const char *iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  
  string_piece() : str_(nullptr), length_(0) {}

  string_piece(const char * const str) : str_(str), length_(str_ ? std::strlen(str_) : 0) {}

  string_piece(const char * const str, const size_type length) : str_(str), length_(length) {}

  string_piece(const std::string &str) : str_(str.c_str()), length_(str.length()) {}

  string_piece(const boost::filesystem::path &str) : str_(str.string().c_str()), length_(str.string().length()) {}

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

  value_type operator [](const size_type i) const { 
    return str_[i];
  }

 private:
  const char * const str_;
  const size_type length_;
};

inline
bool operator ==(const string_piece &lhs, const string_piece &rhs) {
  return !std::strcmp(lhs.c_str(), rhs.c_str());
}

inline
bool operator !=(const string_piece &lhs, const string_piece &rhs) {
  return !(lhs == rhs);
}

inline
bool operator >(const string_piece &lhs, const string_piece &rhs) {
  return std::strcmp(lhs.c_str(), rhs.c_str()) > 0;
}

inline
bool operator <(const string_piece &lhs, const string_piece &rhs) {
  return rhs > lhs;
}

inline
bool operator >=(const string_piece &lhs, const string_piece &rhs) {
  return !(lhs < rhs);
}

inline
bool operator <=(const string_piece &lhs, const string_piece &rhs) {
  return !(lhs > rhs);
}

inline
std::ostream &operator <<(std::ostream &o, const string_piece &piece) {
  return o << piece.c_str();
}
}
