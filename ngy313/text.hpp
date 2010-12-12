#pragma once
#include <string>
#include "detail/texture.hpp"
#include "drawable_base.hpp"
#include "texted.hpp"
#include "font.hpp"

namespace ngy313 {
class text : public drawable_base<text, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag>,
             public detail::texture_base {
 public:
  text(const float x, const float y, const std::string &text, const font &ft)
      : drawable_base(init_vertex(x, y, detail::text_size(ft, text))),
        detail::texture_base(detail::text_image(ft, text).text_texture()) {}

  static vertex_array_type init_vertex(const float x, const float y, const float width, const float height) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF, 0.f, 0.f},
      {{x + width, y, 0.f, 1.f}, 0xFFFFFFFF, 1.f, 0.f},
      {{x, y + height, 0.f, 1.f}, 0xFFFFFFFF, 0.f, 1.f},
      {{x + width, y + height, 0.f, 1.f}, 0xFFFFFFFF, 1.f, 1.f}
    }};
    return vertex;
  }
};
}
