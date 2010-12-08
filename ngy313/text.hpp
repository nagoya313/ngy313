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
  text(const vector2 &pos, const std::string &text, const font &ft)
      : drawable_base(init_vertex(pos, detail::text_size(ft, text))),
        detail::texture_base(detail::text_image(ft, text).text_texture()) {}

  static vertex_array_type init_vertex(const vector2 &pos, const vector2 &size) {
    const vertex_array_type vertex = {{
      {{pos, 0.f, 1.f}, 0xFFFFFFFF, vector2(0.f, 0.f)},
      {{vector2(pos.x() + size.x(), pos.y()), 0.f, 1.f}, 0xFFFFFFFF, vector2(1.f, 0.f)},
      {{vector2(pos.x(), pos.y() + size.y()), 0.f, 1.f}, 0xFFFFFFFF, vector2(0.f, 1.f)},
      {{vector2(pos.x() + size.x(), pos.y() + size.y()), 0.f, 1.f}, 0xFFFFFFFF, vector2(1.f, 1.f)}
    }};
    return vertex;
  }
};
}
