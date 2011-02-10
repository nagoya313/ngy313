#pragma once
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>

namespace ngy313 { namespace graphic {
class pixel : public drawable<pixel, 1, 1, shape_2d_fvf_tag, point_list_primitive_tag> {
 public:
  pixel(const float x, const float y) : vertex_(init_vertex(x, y)) {}

  // –¢ŽÀ‘•
  float x() const {
    return 0.f;
  }

  // –¢ŽÀ‘•
  float y() const {
    return 0.f;
  }

 private:
  vertex_array_type vertex() const {
    return vertex_;
  }

  static vertex_array_type init_vertex(const float x, const float y) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }

  const vertex_array_type vertex_;

  friend class drawable_access;
};
}}