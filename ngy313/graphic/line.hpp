#pragma once
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>

namespace ngy313 { namespace graphic {
class line : public drawable<line, 2, 2, shape_2d_fvf_tag, line_list_primitive_tag> {
 public:
  line(const float x1, const float y1, const float x2, const float y2) 
      : vertex_(init_vertex(x1, y1, x2, y2)) {}

  // ’ñ‹Ÿ‚·‚é‚©–¢’è
  // –¢ŽÀ‘•
  float x1() const {
    return 0.f;
  }

  // –¢ŽÀ‘•
  float y1() const {
    return 0.f;
  }

  // –¢ŽÀ‘•
  float x2() const {
    return 0.f;
  }

  // –¢ŽÀ‘•
  float y2() const {
    return 0.f;
  }

 private:
  vertex_array_type vertex() const {
    return vertex_;
  }

  static vertex_array_type init_vertex(const float x1, const float y1, const float x2, const float y2) {
    const vertex_array_type vertex = {{
      {{x1, y1, 0.f, 1.f}, 0xFFFFFFFF},
      {{x2, y2, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }

  const vertex_array_type vertex_;

  friend class drawable_access;
};
}}