#pragma once
#include <string>
#include "drawable_adaptor.hpp"
#include "font.hpp"
#include "imaged.hpp"
#include "render_target.hpp"

namespace ngy313 { namespace detail {
inline
RECT text_size(const font &ft, const std::string &text) {
  RECT rect = {0, 0, 0, 0};
  drawable_core_access::font1(ft)->DrawText(nullptr, text.c_str(), -1, &rect, DT_CALCRECT, 0xFFFFFFFF);
  return rect;
}

class text_image {
 public:
  text_image(const font &ft, const std::string &text) : rect_(text_size(ft, text)),
                                                        width_(static_cast<float>(rect_.right)),
                                                        height_(static_cast<float>(rect_.bottom)),
                                                        text_(width_, height_) {
    const scoped_render_target target(text_); 
    RECT rect = {0, 0, 0, 0};
    ngy313::clear_screen(0x00000000);
    drawable_core_access::font1(ft)->DrawText(nullptr, text.c_str(), -1, &rect, DT_NOCLIP, 0xFFFFFFFF);
  }

  float width() const {
    return width_;
  }

  float height() const {
    return height_;
  }

 
  friend drawable_core_access;

  const texture_handle &text_texture() const {
    return drawable_core_access::texture1(text_);
  }

 private:
  const RECT rect_;
  const float width_;
  const float height_;
  ngy313::render_target text_;
};

template <typename Drawable>
class texted_adaptor : public index_vertex_adaptor_base<texted_adaptor, Drawable>,
                            public texture_base {
 public:
  template <typename Drawable>
  texted_adaptor(const Drawable &drawable, const text_image &img)
      : index_vertex_adaptor_base(drawable), texture_base(drawable_core_access::texture1(img))  {
    vertex_member_at<rhw_position_t>(pstade::oven::at(vertex_array_, 1)).x += img.width();
    vertex_member_at<rhw_position_t>(pstade::oven::at(vertex_array_, 2)).y += img.height();
    vertex_member_at<rhw_position_t>(pstade::oven::at(vertex_array_, 3)).x += img.width();
    vertex_member_at<rhw_position_t>(pstade::oven::at(vertex_array_, 3)).y += img.height();
  }

 private:
  friend detail::drawable_core_access;

  typename Drawable::vertex_range_type vertex_range() const {
    return pstade::oven::make_range(vertex_array_);
  }
};

struct texted : public adaptor_result<texted_adaptor> {
  explicit texted(const font &ft, const std::string &name) : image_(ft, name) {}

  template <typename Drawable>
  texted_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return texted_adaptor<Drawable>(drawable, image_);
  }

 private:
  const text_image image_;
};
}}

namespace ngy313 {
using detail::texted;
}