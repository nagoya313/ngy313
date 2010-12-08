#pragma once
#include "drawable_base.hpp"
#include "vector.hpp"

namespace ngy313 {
class line3d : public drawable_base<line3d, 2, 2, shape_3d_fvf_tag, line_list_primitive_tag> {
 public:
  line3d(const vector3 &p1, const vector3 &p2) : drawable_base(init_vertex(p1, p2)) {}

 private:
  static vertex_array_type init_vertex(const vector3 &p1, const vector3 &p2) {
    const vertex_array_type vertex = {{
      {p1, 0xFFFFFFFF}, {p2, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class triangle3d : public drawable_base<triangle3d, 3, 1, shape_3d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  triangle3d(const vector3 &p1, const vector3 &p2, const vector3 &p3) : drawable_base(init_vertex(p1, p2, p3)) {}

 private:
  static vertex_array_type init_vertex(const vector3 &p1, const vector3 &p2, const vector3 &p3) {
    const vertex_array_type vertex = {{
      {p1, 0xFFFFFFFF}, {p2, 0xFFFFFFFF}, {p3, 0xFFFFFFFF}
    }};
    return vertex;
  }
};
}
