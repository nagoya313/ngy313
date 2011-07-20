#ifndef NGY313_STRING_WRAP_HPP_
#define NGY313_STRING_WRAP_HPP_

#include <cstring>
#include <algorithm>
#include <iosfwd>
#include <string>
#include <boost/operators.hpp>
#include <boost/range/iterator_range.hpp>

namespace ngy313 { 
template <typename Char>
class basic_string_wrap : public boost::iterator_range<const Char *>,
                          boost::equality_comparable<basic_string_wrap<Char>>,
                          boost::less_than_comparable<basic_string_wrap<Char>> {
  typedef boost::iterator_range<const Char *> base_type;

 public:
  basic_string_wrap() : base_type(nullptr, nullptr) {}

  basic_string_wrap(const Char *str)
      : base_type(str, str + std::strlen(str)) {}

  template <typename CharTraits, typename Allocator>
  basic_string_wrap(const std::basic_string<Char,
  		                                        CharTraits,
  		                                        Allocator> &str)
      : base_type() {
    const char * const p = str.c_str();
    base_type::operator=(base_type(p, p + str.size()));
  }

  basic_string_wrap(const Char *offset, typename base_type::size_type len)
      : base_type(offset, offset + len) {}

  const Char *c_str() const {
    return base_type::begin();
  }

  typename base_type::size_type length() const {
    return base_type::size();
  }

  std::basic_string<Char> string() const {
    return std::basic_string<Char>(!base_type::empty() ?
    		                            base_type::begin() :
    		                            "", base_type::size());
  }
};

template <typename Char>
bool operator ==(const basic_string_wrap<Char> &rhs,
                 const basic_string_wrap<Char> &lhs) {
  return !std::memcmp(lhs.data(),
                      rhs.data(),
                      std::min(lhs.size(), 
                               rhs.size())) && rhs.size() == lhs.size();
}

template <typename Char>
bool operator <(const basic_string_wrap<Char> &lhs,
                const basic_string_wrap<Char> &rhs) {
  const int r = std::memcmp(lhs.data(), 
                            rhs.data(),
                            std::min(lhs.size(), rhs.size()));
  return (r < 0 || (!r && lhs.size() < rhs.size()));
}

template <typename Char>
std::ostream& operator<<(std::ostream &o,
                         const basic_string_wrap<Char> &piece) {
  return o << piece.c_str();
}

typedef basic_string_wrap<char> string_wrap;
}

#endif
