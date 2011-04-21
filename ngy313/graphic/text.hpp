#ifndef NGY313_GRAPHIC_TEXT_HPP_
#define NGY313_GRAPHIC_TEXT_HPP_
#include <utility>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2/trackable.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/texture.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/texture.hpp>
#endif
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
class text_image : public boost::signals2::trackable, private boost::noncopyable {
 public: 
  text_image(const utility::string_piece &str, const font &ft) : font_(font_access::font(ft)), 
                                                                 size_(text_size(str, ft)),
                                                                 str_(str.string()),
                                                                 text_(size_.first, size_.second) {
    text_.connect_after_reset(boost::bind(&text_image::render, this));
    render();
  }

  int width() const {
    return size_.first;
  }

  int height() const {
    return size_.second;
  }

  std::string string() const {
    return str_;
  }

 private:
  static std::pair<int, int> text_size(const utility::string_piece &text, const font &ft) {
    RECT rect = {0, 0, 0, 0};
    font_access::font(ft)->DrawTextA(nullptr, text.c_str(), -1, &rect, DT_CALCRECT, utility::kWhite);
    return std::make_pair(rect.right, rect.bottom);
  }

  void render() {
    const scoped_render render;
    const scoped_render_target target(text_); 
    clear_screen(utility::kClear);
    RECT rect = {0, 0, 0, 0};
    font_->DrawTextA(nullptr, str_.c_str(), -1, &rect, DT_NOCLIP, utility::kWhite);
  }

  const detail::texture_handle &texture1() const {
    return detail::texture_core_access::texture1(text_);
  }

  const detail::font_handle &font_;
  const std::pair<int, int> size_;
  const std::string str_;
  render_target text_;

  friend class detail::texture_core_access;
};

class text : public drawable<text, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  text(const float x, const float y, const utility::string_piece &str, const font &ft) 
      : image_(text_image(str, ft)), texture_(image_), x_(x), y_(y) {}

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x_, y_), diffuse_t(0xFFFFFFFF), tex_t<1>(0.f, 0.f)),
      vertex_type(rhw_position_t(x_ + image_.width(), y_), diffuse_t(0xFFFFFFFF), tex_t<1>(1.f, 0.f)),
      vertex_type(rhw_position_t(x_, y_ + image_.height()), diffuse_t(0xFFFFFFFF), tex_t<1>(0.f, 1.f)),
      vertex_type(rhw_position_t(x_ + image_.width(), y_ + image_.height()), diffuse_t(0xFFFFFFFF), tex_t<1>(1.f, 1.f))
    }};
    return vertex;
  }

  const texture &texture1() const {
    return texture_;
  }

  text_image image_;
  texture texture_;
  float x_;
  float y_;

  friend class drawable_access;
  friend class texture_access;
};
}}

#endif
