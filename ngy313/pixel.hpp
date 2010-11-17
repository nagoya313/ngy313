#pragma once
#include "drawable_base.hpp"

namespace ngy313 {
class pixel
    : public drawable_base<pixel, 1, 1, shape_2d_fvf_tag, point_list_primitive_tag> {
 public:
  pixel(const float x, const float y) : drawable_base(init_vertex(x, y)) {}

 private:
  static vertex_array_type init_vertex(const float x, const float y) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};
}