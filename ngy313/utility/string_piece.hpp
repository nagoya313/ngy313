#ifndef NGY313_UTILITY_STRING_PIECE_HPP_
#define NGY313_UTILITY_STRING_PIECE_HPP_
#include <string>

namespace ngy313 { namespace utility {
// 引数で渡す程度の用途しか考えていない
// Googleとかにあるような汎用性を持たせるかは未定

class string_piece {
 public:
  string_piece(const char * const str) : str_(str) {}

  string_piece(const std::string &str) : str_(str.c_str()) {}

  const char *c_str() const {
    return str_;
  }

  std::string string() const {
    return std::string(c_str());
  }

 private:
  const char *str_;
};
}}

#endif
