#pragma once
#include <pstade/oven/make_range.hpp>
#include "drawable_adaptor.hpp"

namespace ngy313 {
class line_box
    : public drawable_adaptor<line_box, 5, 4, make_drawable_tag<dimension2_fvf_tag,
                                                                diffuse_fvf_tag,
                                                                line_strip_primitive_tag>> {
 public:
  line_box(const float x, const float y, const float width, const float height) 
      : vertex_(init(x, y, width, height)) {}

  vertex_range_type vertex() const {
    return pstade::oven::make_range(vertex_.begin(), vertex_.end());
  }

 private:
  static vertex_array_type init(const float x, const float y, const float width, const float height) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }

  const vertex_array_type vertex_;
};
}