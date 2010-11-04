#pragma once
#include <pstade/oven/make_range.hpp>
#include "drawable_adaptor.hpp"

namespace ngy313 {
class triangle 
  : public drawable_adaptor<triangle, 3, 1, make_drawable_tag<dimension2_fvf_tag, 
                                                             diffuse_fvf_tag, 
                                                             triangle_list_primitive_tag>> {
 public:
  triangle(const float x1, 
           const float y1,
           const float x2, 
           const float y2, 
           const float x3,
           const float y3) 
      : vertex_(init_vertex(x1, y1, x2, y2, x3, y3)) {}

  vertex_range_type vertex() const {
    return pstade::oven::make_range(vertex_.begin(), vertex_.end());
  }

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
      {{x3, y3, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }

  const vertex_array_type vertex_;
};
}