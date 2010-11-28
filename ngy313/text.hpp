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

  text(const vector2 &pos, const std::string &text, const font &ft)
      : detail::text_image(ft, text),
        drawable_base(init_vertex(pos, *this)),
        detail::texture_base(text_texture()) {}

  static vertex_array_type init_vertex(const vector2 &pos, const detail::text_image &img) {
    const vertex_array_type vertex = {{
      {{pos, 0.f, 1.f}, 0xFFFFFFFF, vector2(0.f, 0.f)},
      {{vector2(pos.x() + img.width(), pos.y()), 0.f, 1.f}, 0xFFFFFFFF, vector2(1.f, 0.f)},
      {{vector2(pos.x(), pos.y() + img.height()), 0.f, 1.f}, 0xFFFFFFFF, vector2(0.f, 1.f)},
      {{vector2(pos.x() + img.width(), pos.y() + img.height()), 0.f, 1.f}, 0xFFFFFFFF, vector2(1.f, 1.f)}
    }};
    return vertex;
  }
};
}

#pragma warning(default: 4355)