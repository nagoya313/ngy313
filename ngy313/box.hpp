#pragma once
#include <pstade/oven/make_range.hpp>
#include "drawable_adaptor.hpp"

namespace ngy313 {
class box
    : public drawable_adaptor<box,
                              4, 
                              2,
                              make_drawable_tag<dimension2_fvf_tag, 
                                                diffuse_fvf_tag, 
                                                triangle_strip_primitive_tag>> {
 public:
  box(const float x, const float y, const float width, const float height) 
      : drawable_adaptor(init_vertex(x, y, width, height)) {}

  template <typename Filter>
  explicit box(const Filter &filter) : drawable_adaptor(filter) {}

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