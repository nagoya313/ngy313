#pragma once
#include <cassert>
#include "detail/texture_base.hpp"
#include "drawable_base.hpp"
#include "vector.hpp"

namespace ngy313 {
class texture : public drawable_base<texture, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  texture(const float x, const float y, const float width, const float height)
      : drawable_base(init_vertex(x, y, width, height)) {}

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float width, const float height) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF, {0.f, 0.f}},
      {{x + width, y, 0.f, 1.f}, 0xFFFFFFFF, {1.f, 0.f}},
      {{x, y + height, 0.f, 1.f}, 0xFFFFFFFF, {0.f, 1.f}},
      {{x + width, y + height, 0.f, 1.f}, 0xFFFFFFFF, {1.f, 1.f}}
    }};
    return vertex;
  }
};

class texture3d : public drawable_base<texture3d, 4, 2, image_3d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  texture3d(const vector3 &pos, const float width, const float height)
      : drawable_base(init_vertex(pos, width, height)) {}

 private:
  static vertex_array_type init_vertex(const vector3 &pos, const float width, const float height) {
    const vertex_array_type vertex = {{
      {{pos.x(), pos.y(), 0.f}, 0xFFFFFFFF, {0.f, 0.f}},
      {{pos.x() + width, pos.y(), 0.f}, 0xFFFFFFFF, {1.f, 0.f}},
      {{pos.x(), pos.y() + height, 0.f}, 0xFFFFFFFF, {0.f, 1.f}},
      {{pos.x() + width, pos.y() + height, 0.f}, 0xFFFFFFFF, {1.f, 1.f}}
    }};
    return vertex;
  }
};
} 