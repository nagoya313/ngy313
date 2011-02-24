#pragma once
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
#pragma warning(disable: 4512)

class line : public drawable<line, 2, 2, shape_2d_fvf_tag, line_list_primitive_tag> {
 public:
  line(const float x1, const float y1, const float x2, const float y2) 
      : vertex_(init_vertex(x1, y1, x2, y2)) {}

  float x1() const {
    return vertex_member_at<position>(vertex_[0]).x;
  }

  float y1() const {
    return vertex_member_at<position>(vertex_[0]).y;
  }

  float x2() const {
    return vertex_member_at<position>(vertex_[1]).x;
  }

  float y2() const {
    return vertex_member_at<position>(vertex_[1]).y;
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

#pragma warning(default: 4512)
}}