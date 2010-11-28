#pragma once
#include <cmath>
#include <boost/preprocessor/repeat_from_to.hpp>
#include "detail/shape_position.hpp"
#include "drawable_base.hpp"

namespace ngy313 {
class pixel : public drawable_base<pixel, 1, 1, shape_2d_fvf_tag, point_list_primitive_tag> {
 public:
  explicit pixel(const vector2 &pos) : drawable_base(init_vertex(pos)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos) {
    const vertex_array_type vertex = {{
      {{pos, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class line : public drawable_base<line, 2, 2, shape_2d_fvf_tag, line_list_primitive_tag> {
 public:
  line(const vector2 &pos1, const vector2 &pos2) 
      : drawable_base(init_vertex(pos1, pos2)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos1, const vector2 &pos2) {
    const vertex_array_type vertex = {{
      {{pos1, 0.f, 1.f}, 0xFFFFFFFF},
      {{pos2, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class triangle : public drawable_base<triangle, 3, 1, shape_2d_fvf_tag, triangle_list_primitive_tag> {
 public:
  triangle(const vector2 &pos1, const vector2 &pos2, const vector2 &pos3) 
      : drawable_base(init_vertex(pos1, pos2, pos3)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos1, const vector2 &pos2, const vector2 &pos3) {
    const vertex_array_type vertex = {{
      {{pos1, 0.f, 1.f}, 0xFFFFFFFF},
      {{pos2, 0.f, 1.f}, 0xFFFFFFFF},
      {{pos3, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class line_triangle : public drawable_base<line_triangle, 4, 3, shape_2d_fvf_tag, line_strip_primitive_tag> {
 public:
  line_triangle(const vector2 &pos1, const vector2 &pos2, const vector2 &pos3) 
      : drawable_base(init_vertex(pos1, pos2, pos3)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos1, const vector2 &pos2, const vector2 &pos3) {
    const vertex_array_type vertex = {{
      {{pos1, 0.f, 1.f}, 0xFFFFFFFF},
      {{pos2, 0.f, 1.f}, 0xFFFFFFFF},
      {{pos3, 0.f, 1.f}, 0xFFFFFFFF},
      {{pos1, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class box : public drawable_base<box, 4, 2, shape_2d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  box(const vector2 &pos, const vector2 &size)
      : drawable_base(init_vertex(pos, size)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos, const vector2 &size) {
    const vertex_array_type vertex = {{
      {{pos, 0.f, 1.f}, 0xFFFFFFFF},
      {{vector2(pos.x() + size.x(), pos.y()), 0.f, 1.f}, 0xFFFFFFFF},
      {{vector2(pos.x(), pos.y() + size.y()), 0.f, 1.f}, 0xFFFFFFFF},
      {{pos + size, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class line_box : public drawable_base<line_box, 5, 4, shape_2d_fvf_tag, line_strip_primitive_tag> {
 public:
  line_box(const vector2 &pos, const vector2 &size) 
      : drawable_base(init_vertex(pos, size)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos, const vector2 &size) {
    const vertex_array_type vertex = {{
      {{pos, 0.f, 1.f}, 0xFFFFFFFF},
      {{vector2(pos.x() + size.x(), pos.y()), 0.f, 1.f}, 0xFFFFFFFF},
      {{pos + size, 0.f, 1.f}, 0xFFFFFFFF},
      {{vector2(pos.x(), pos.y() + size.y()), 0.f, 1.f}, 0xFFFFFFFF},
      {{pos, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

#define NGY313_CIRCLE_VERTEX_SIZE 62

#define NGY313_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
{{vector2(pos.x() + std::cos(detail::vertex_radian<circle, n>::value) * r,\
  pos.y() + std::sin(detail::vertex_radian<circle, n>::value) * r),\
  0.f,\
  1.f}, 0xFFFFFFFF},

class circle
    : public drawable_base<circle, NGY313_CIRCLE_VERTEX_SIZE, 60, shape_2d_fvf_tag, triangle_fan_primitive_tag> {
 public:
  circle(const vector2 &pos, const float r) : drawable_base(init_vertex(pos, r)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos, const float r) {
    const vertex_array_type vertex = {{
      {{pos, 0.f, 1.f}, 0xFFFFFFFF},
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_CIRCLE_VERTEX_SIZE, NGY313_CIRCLE_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }
};

#undef NGY313_CIRCLE_VERTEX_ELEM_GEN

#undef NGY313_CIRCLE_VERTEX_SIZE

#define NGY313_LINE_CIRCLE_VERTEX_SIZE 60

#define NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
{{vector2(pos.x() + std::cos(detail::line_vertex_radian<line_circle, n>::value) * r,\
  pos.y() + std::sin(detail::line_vertex_radian<line_circle, n>::value) * r),\
  0.f,\
  1.f}, 0xFFFFFFFF},

class line_circle : public drawable_base<line_circle, 
                                         NGY313_LINE_CIRCLE_VERTEX_SIZE, 
                                         59, 
                                         shape_2d_fvf_tag,
                                         line_strip_primitive_tag> {
 public:
  line_circle(const vector2 &pos, const float r) : drawable_base(init_vertex(pos, r)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos, const float r) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_CIRCLE_VERTEX_SIZE, NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }
};

#undef NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN

#define NGY313_OVAL_VERTEX_SIZE 62

#define NGY313_OVAL_VERTEX_ELEM_GEN(z, n, data)\
{{vector2(pos.x() + std::cos(detail::vertex_radian<oval, n>::value) * r.x(),\
  pos.y() + std::sin(detail::vertex_radian<oval, n>::value) * r.y()),\
  0.f,\
  1.f}, 0xFFFFFFFF},

class oval : public drawable_base<oval, NGY313_OVAL_VERTEX_SIZE, 60, shape_2d_fvf_tag, triangle_fan_primitive_tag> {
 public:
  oval(const vector2 &pos, const vector2 &r) : drawable_base(init_vertex(pos, r)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos, const vector2 &r) {
    const vertex_array_type vertex = {{
      {{pos, 0.f, 1.f}, 0xFFFFFFFF},
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_OVAL_VERTEX_SIZE, NGY313_OVAL_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }
};

#undef NGY313_OVAL_VERTEX_ELEM_GEN

#undef NGY313_OVAL_VERTEX_SIZE

#define NGY313_LINE_OVAL_VERTEX_SIZE 60

#define NGY313_LINE_OVAL_VERTEX_ELEM_GEN(z, n, data)\
{{vector2(pos.x() + std::cos(detail::line_vertex_radian<line_oval, n>::value) * r.x(),\
  pos.y() + std::sin(detail::line_vertex_radian<line_oval, n>::value) * r.y()),\
  0.f,\
  1.f}, 0xFFFFFFFF},

class line_oval : public drawable_base<line_oval, 
                                       NGY313_LINE_OVAL_VERTEX_SIZE,
                                       59,
                                       shape_2d_fvf_tag, 
                                       line_strip_primitive_tag> {
 public:
  line_oval(const vector2 &pos, const vector2 &r)
      : drawable_base(init_vertex(pos, r)) {}

 private:
  static vertex_array_type init_vertex(const vector2 &pos, const vector2 &r) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_OVAL_VERTEX_SIZE, NGY313_LINE_OVAL_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }
};

#undef NGY313_LINE_OVAL_VERTEX_ELEM_GEN

#undef NGY313_LINE_OVAL_VERTEX_SIZE
}
