#pragma once
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
#pragma warning(disable: 4512)

class pixel : public drawable<pixel, 1, 1, shape_2d_fvf_tag, point_list_primitive_tag> {
 public:
  pixel(const float x, const float y) : vertex_(init_vertex(x, y)) {}

  float x() const {
    return vertex_member_at<position>(vertex_[0]).x;
  }

  float y() const {
    return vertex_member_at<position>(vertex_[0]).y;
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

#pragma warning(default: 4512)
}}