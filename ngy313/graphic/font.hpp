#ifndef NGY313_GRAPHIC_FONT_HPP_
#define NGY313_GRAPHIC_FONT_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/font.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/font.hpp>
#endif

namespace ngy313 { namespace graphic {
class font : private boost::noncopyable {
 public:
  font(const int size, const utility::string_piece &name) : font_(size, name) {}

  int size() const {
    font_.name();
  }

  std::string name() const {
    font_.name();
  }

 private:
  const detail::font_handle &handle() const {
    return font_.font();
  }

  const detail::font_type font_;

  friend class font_access;
};

class font_access {
 private:
  static const detail::font_handle &font(const font &ft) {
    return ft.handle();
  }

  friend class text_image;
};
}}

#endif
