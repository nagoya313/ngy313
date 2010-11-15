#pragma once
#include "drawable_base.hpp"

namespace ngy313 {
class box
    : public drawable_base<box,
                           4, 
                           2,
                           shape_2d_fvf_tag, 
                           triangle_strip_primitive_tag> {
 public:
  box(const float x, const float y, const float width, const float height) 
      : drawable_base(init_vertex(x, y, width, height)) {}

 private:
  static vertex_array_type init_vertex(const float x, 
                                       const float y, 
                                       const float width, 
                                       const float height) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y + height, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};
}