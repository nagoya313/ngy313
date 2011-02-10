#pragma once
#include <boost/bind.hpp>
#include <boost/signals2/trackable.hpp>
#include <ngy313/graphic/detail/font.hpp>

namespace ngy313 { namespace graphic {
class font : public boost::signals2::trackable {
 public:
  font(const int size, const utility::string_piece &name) : font_(detail::init_font_key(size, name)) {
    detail::before_reset().connect(boost::bind(&font::release, this));
    detail::after_reset().connect(boost::bind(&font::reset, this));
  }

 private:
  const detail::font_handle &handle() const {
    return font_.get().font();
  }

  void release() {
    font_.get().font()->OnLostDevice();
  }

  void reset() {
    font_.get().font()->OnResetDevice();
  }

  const detail::font_type font_;

  friend class font_access;
};

class font_access {
private:
  static detail::font_handle font(const font &ft) {
    return ft.handle();
  }

  friend class text_image;
};
}}
