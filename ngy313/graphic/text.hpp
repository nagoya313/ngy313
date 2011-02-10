#pragma once
#include <utility>
#include <boost/bind.hpp>
#include <boost/signals2/trackable.hpp>
#include <ngy313/graphic/detail/texture.hpp>
#include <ngy313/graphic/texture.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/font.hpp>
#include <ngy313/graphic/graphic.hpp>
#include <ngy313/graphic/render_target.hpp>
#include <ngy313/graphic/scoped_render.hpp>
#include <ngy313/utility/color_code.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic {
class text_image : public boost::signals2::trackable {
 public: 
  text_image(const utility::string_piece &str, const font &ft) : font_(font_access::font(ft)), 
                                                                 size_(text_size(str, ft)),
                                                                 str_(str.string()),
                                                                 text_(size_.first, size_.second) {
    text_.connect_after_reset(boost::bind(&text_image::render, this));
    render();
  }

  float width() const {
    return size_.first;
  }

  float height() const {
    return size_.second;
  }

  std::string string() const {
    return str_;
  }

 private:
  static std::pair<float, float> text_size(const utility::string_piece &text, const font &ft) {
    RECT rect = {0, 0, 0, 0};
    font_access::font(ft)->DrawText(nullptr, text.c_str(), -1, &rect, DT_CALCRECT, utility::kWhite);
    return std::make_pair(static_cast<float>(rect.right), static_cast<float>(rect.bottom));
  }

  void render() {
    const scoped_render render;
    const scoped_render_target target(text_); 
    clear_screen(utility::kClear);
    RECT rect = {0, 0, 0, 0};
    font_->DrawText(nullptr, str_.c_str(), -1, &rect, DT_NOCLIP, utility::kWhite);
  }

  const detail::texture_handle &texture1() const {
    return detail::texture_access::texture1(text_);
  }

  const detail::font_handle font_;
  const std::pair<float, float> size_;
  const std::string str_;
  render_target text_;

  friend class detail::texture_access;
  friend class detail::texture_core_access;
};

class text : public drawable<text, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag>, public texture {
 public:
  text(const float x, const float y, const utility::string_piece &str, const font &ft) 
      : texture(text_image(str, ft)), x_(x), y_(y) {}

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
      {{x_, y_, 0.f, 1.f}, 0xFFFFFFFF, 0.f, 0.f},
      {{x_ + width(), y_, 0.f, 1.f}, 0xFFFFFFFF, 1.f, 0.f},
      {{x_, y_ + height(), 0.f, 1.f}, 0xFFFFFFFF, 0.f, 1.f},
      {{x_ + width(), y_ + height(), 0.f, 1.f}, 0xFFFFFFFF, 1.f, 1.f}
    }};
    return vertex;
  }

  const float x_;
  const float y_;

  friend class drawable_access;
};
}}