#pragma once
#include <pstade/oven/make_range.hpp>
#include "drawable_adaptor.hpp"

namespace ngy313 {
class line
    : public drawable_adaptor<line, 
                              2, 
                              2,
                              make_drawable_tag<dimension2_fvf_tag, 
                                                diffuse_fvf_tag, 
                                                line_list_primitive_tag>> {
 public:
  line(const float x1, const float y1, const float x2, const float y2) 
      : vertex_(init_vertex(x1, y1, x2, y2)) {}

  vertex_range_type vertex() const {
    return pstade::oven::make_range(vertex_.begin(), vertex_.end());
  }

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

  const vertex_array_type vertex_;
};
}