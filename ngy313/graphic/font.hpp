#pragma once
#include <ngy313/graphic/detail/font.hpp>

namespace ngy313 { namespace graphic {
#pragma warning(disable: 4512)

class font {
 public:
  font(const int size, const utility::string_piece &name) : font_(detail::init_font_key(size, name)) {}

 private:
  const detail::font_handle &handle() const {
    return font_.get().font();
  }

  const detail::font_type font_;

  friend class font_access;
};

#pragma warning(default: 4512)

class font_access {
private:
  static const detail::font_handle &font(const font &ft) {
    return ft.handle();
  }

  friend class text_image;
};
}}
