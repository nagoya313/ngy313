#pragma once
#pragma warning(disable: 4355)
#include <string>
#include "detail/texture.hpp"
#include "drawable_base.hpp"
#include "texted.hpp"
#include "font.hpp"

namespace ngy313 {
class text : private detail::text_image,
             public drawable_base<text, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag>,
             public detail::texture_base {
 public:
  friend detail::drawable_core_access;

  text(const float x, const float y, const std::string &text, const font &ft)
      : detail::text_image(ft, text),
        drawable_base(init_vertex(x, y, *this)),
        detail::texture_base(text_texture()) {}

  static vertex_array_type init_vertex(const float x, const float y, const detail::text_image &img) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF, {0.f, 0.f}},
      {{x + img.width(), y, 0.f, 1.f}, 0xFFFFFFFF, {1.f, 0.f}},
      {{x, y + img.height(), 0.f, 1.f}, 0xFFFFFFFF, {0.f, 1.f}},
      {{x + img.width(), y + img.height(), 0.f, 1.f}, 0xFFFFFFFF, {1.f, 1.f}}
    }};
    return vertex;
  }
};
}

#pragma warning(default: 4355)