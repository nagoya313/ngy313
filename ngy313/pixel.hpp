#pragma once
#include <pstade/oven/make_range.hpp>
#include "drawable_adaptor.hpp"

namespace ngy313 {
class pixel
    : public drawable_adaptor<pixel, 
                              1,
                              1,
                              make_drawable_tag<dimension2_fvf_tag, 
                                                diffuse_fvf_tag, 
                                                point_list_primitive_tag>> {
 public:
  pixel(const float x, const float y) : vertex_(init_vertex(x, y)) {}

  vertex_range_type vertex() const {
    return pstade::oven::make_range(vertex_.begin(), vertex_.end());
  }

 private:
  static vertex_array_type init_vertex(const float x, const float y) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }

  const vertex_array_type vertex_;
};
}