#pragma once
#include "detail/string_piece.hpp"
#include "drawable_adaptor.hpp"
#include "font.hpp"
#include "imaged.hpp"
#include "graphic.hpp
#include "vector.hpp"

namespace ngy313 { namespace detail {
inline
vector2 text_size(const font &ft, const string_piece &text) {
  RECT rect = {0, 0, 0, 0};
  drawable_core_access::font1(ft)->DrawText(nullptr, text.c_str(), -1, &rect, DT_CALCRECT, 0xFFFFFFFF);
  return vector2(static_cast<float>(rect.right), static_cast<float>(rect.bottom));
}

class text_image {
 public:
  text_image(const font &ft, const string_piece &text) : size_(text_size(ft, text)), text_(size_) {
    const scoped_render_target target(text_); 
    RECT rect = {0, 0, 0, 0};
    clear_screen(0x00000000);
    drawable_core_access::font1(ft)->DrawText(nullptr, text.c_str(), -1, &rect, DT_NOCLIP, 0xFFFFFFFF);
  }

  float width() const {
    return size_.x();
  }

  float height() const {
    return size_.y();
  }
 
  friend drawable_core_access;

  const texture_handle &text_texture() const {
    return drawable_core_access::texture1(text_);
  }

 private:
  const vector2 size_;
  render_target text_;
};
}}