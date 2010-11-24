#pragma once
#include <boost/signals2/trackable.hpp>
#include <boost/bind.hpp>
#include "detail/window_singleton.hpp"
#include "detail/drawable_core_access.hpp"
#include "detail/font.hpp"

namespace ngy313 {
class font : public boost::signals2::trackable {
 public:
  font(const int size, const string_piece &name) : font_(detail::create_font(detail::graphic_device(), size, name)) {
    detail::before_reset().connect(boost::bind(&font::release, this));
    detail::after_reset().connect(boost::bind(&font::reset, this));
  }

 private:
  friend detail::drawable_core_access;

  void release() {
    font_->OnLostDevice();
  }

  void reset() {
    font_->OnResetDevice();
  }

  const detail::font_handle &handle() const {
    return font_;
  }

  const detail::font_handle font_;
};
}