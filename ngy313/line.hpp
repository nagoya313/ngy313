#pragma once
#include "drawable_base.hpp"

namespace ngy313 {
class line
    : public drawable_base<line, 
                           2, 
                           2,
                           shape_2d_fvf_tag, 
                           line_list_primitive_tag> {
 public:
  line(const float x1, const float y1, const float x2, const float y2) 
      : drawable_base(init_vertex(x1, y1, x2, y2)) {}

 private:
  static vertex_array_type init_vertex(const float x1, 
                                       const float y1,
                                       const float x2,
                                       const float y2) {
    const vertex_array_type vertex = {{
      {{x1, y1, 0.f, 1.f}, 0xFFFFFFFF},
      {{x2, y2, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};
}