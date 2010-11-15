#pragma once
#include "drawable_base.hpp"

namespace ngy313 {
class line_triangle 
  : public drawable_base<line_triangle,
                         4,
                         3,
                         shape_2d_fvf_tag, 
                         line_strip_primitive_tag> {
 public:
  line_triangle(const float x1, 
                const float y1,
                const float x2, 
                const float y2, 
                const float x3,
                const float y3) 
      : drawable_base(init_vertex(x1, y1, x2, y2, x3, y3)) {}

 private:
  static vertex_array_type init_vertex(const float x1, 
                                       const float y1,
                                       const float x2, 
                                       const float y2, 
                                       const float x3, 
                                       const float y3) {
    const vertex_array_type vertex = {{
      {{x1, y1, 0.f, 1.f}, 0xFFFFFFFF},
      {{x2, y2, 0.f, 1.f}, 0xFFFFFFFF},
      {{x3, y3, 0.f, 1.f}, 0xFFFFFFFF},
      {{x1, y1, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};
}