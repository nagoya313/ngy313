#ifndef NGY313_FONT_HPP_
#define NGY313_FONT_HPP_

#include <string>
#include <ngy313/string_wrap.hpp>

#if defined(_WIN32)
#elif defined(__linux__)
#include <ngy313/detail/cairomm_font.hpp>
#endif

namespace ngy313 {
template <typename Font>
class basic_font {
 public:
  explicit basic_font(const string_wrap &name, int size) : font_(name, size) {}
  
  std::string name() const {
    return font_.name();
  }
  
  int size() const {
    return font_.size();
  }
  
  typename Font::handle_type handle() const {
    return font_.handle();
  }
  
 private:
  Font font_;
};

#if defined(_WIN32)
#elif defined(__linux__)
typedef basic_font<detail::cairomm_font> font;
#endif
}

#endif