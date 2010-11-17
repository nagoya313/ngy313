#pragma once
#include "drawable_base.hpp"

namespace ngy313 {
class line_box : public drawable_base<line_box, 5, 4, shape_2d_fvf_tag, line_strip_primitive_tag> {
 public:
  line_box(const float x, const float y, const float width, const float height) 
      : drawable_base(init_vertex(x, y, width, height)) {}

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float width, const float height) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};
}