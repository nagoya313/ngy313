#pragma once
#include <cmath>
#include <boost/preprocessor/repeat_from_to.hpp>
#include "detail/shape_position.hpp"
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

class line : public drawable_base<line, 2, 2, shape_2d_fvf_tag, line_list_primitive_tag> {
 public:
  line(const float x1, const float y1, const float x2, const float y2) 
      : drawable_base(init_vertex(x1, y1, x2, y2)) {}

 private:
  static vertex_array_type init_vertex(const float x1, const float y1, const float x2, const float y2) {
    const vertex_array_type vertex = {{
      {{x1, y1, 0.f, 1.f}, 0xFFFFFFFF},
      {{x2, y2, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class triangle : public drawable_base<triangle, 3, 1, shape_2d_fvf_tag, triangle_list_primitive_tag> {
 public:
  triangle(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3) 
      : drawable_base(init_vertex(x1, y1, x2, y2, x3, y3)) {}

 private:
  static vertex_array_type init_vertex(const float x1, 
                                       const float y1,
                                       const float x2, 
                                       const float y2, 
                                       const float x3, 
                                       const float y3) {
    const vertex_array_type vertex = {{
      {{x1, y1, 0.f, 1.f}, 0xFFFFFFFF},
      {{x2, y2, 0.f, 1.f}, 0xFFFFFFFF},
      {{x3, y3, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class line_triangle : public drawable_base<line_triangle, 4, 3, shape_2d_fvf_tag, line_strip_primitive_tag> {
 public:
  line_triangle(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3) 
      : drawable_base(init_vertex(x1, y1, x2, y2, x3, y3)) {}

 private:
  static vertex_array_type init_vertex(const float x1, 
                                       const float y1,
                                       const float x2, 
                                       const float y2, 
                                       const float x3, 
                                       const float y3) {
    const vertex_array_type vertex = {{
      {{x1, y1, 0.f, 1.f}, 0xFFFFFFFF},
      {{x2, y2, 0.f, 1.f}, 0xFFFFFFFF},
      {{x3, y3, 0.f, 1.f}, 0xFFFFFFFF},
      {{x1, y1, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class box : public drawable_base<box, 4, 2, shape_2d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  box(const float x, const float y, const float width, const float height)
      : drawable_base(init_vertex(x, y, width, height)) {}

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float width, const float height) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y + height, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

class line_box : public drawable_base<line_box, 5, 4, shape_2d_fvf_tag, line_strip_primitive_tag> {
 public:
  line_box(const float x, const float y, const float width, const float height) 
      : drawable_base(init_vertex(x, y, width, height)) {}

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float width, const float height) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y, 0.f, 1.f}, 0xFFFFFFFF},
      {{x + width, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y + height, 0.f, 1.f}, 0xFFFFFFFF},
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF}
    }};
    return vertex;
  }
};

#define NGY313_CIRCLE_VERTEX_SIZE 62

#define NGY313_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(detail::vertex_radian<circle, n>::value) * r,\
  y + std::sin(detail::vertex_radian<circle, n>::value) * r,\
  0.f,\
  1.f}, 0xFFFFFFFF},

class circle
    : public drawable_base<circle, NGY313_CIRCLE_VERTEX_SIZE, 60, shape_2d_fvf_tag, triangle_fan_primitive_tag> {
 public:
  circle(const float x, const float y, const float r) : drawable_base(init_vertex(x, y, r)) {}

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float r) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_CIRCLE_VERTEX_SIZE, NGY313_CIRCLE_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }
};

#undef NGY313_CIRCLE_VERTEX_ELEM_GEN

#undef NGY313_CIRCLE_VERTEX_SIZE

#define NGY313_LINE_CIRCLE_VERTEX_SIZE 60

#define NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(detail::line_vertex_radian<line_circle, n>::value) * r,\
  y + std::sin(detail::line_vertex_radian<line_circle, n>::value) * r,\
  0.f,\
  1.f}, 0xFFFFFFFF},

class line_circle : public drawable_base<line_circle, 
                                         NGY313_LINE_CIRCLE_VERTEX_SIZE, 
                                         59, 
                                         shape_2d_fvf_tag,
                                         line_strip_primitive_tag> {
 public:
  line_circle(const float x, const float y, const float r) : drawable_base(init_vertex(x, y, r)) {}

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float r) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_CIRCLE_VERTEX_SIZE, NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }
};

#undef NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN

#define NGY313_OVAL_VERTEX_SIZE 62

#define NGY313_OVAL_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(detail::vertex_radian<oval, n>::value) * rx,\
  y + std::sin(detail::vertex_radian<oval, n>::value) * ry,\
  0.f,\
  1.f}, 0xFFFFFFFF},

class oval : public drawable_base<oval, NGY313_OVAL_VERTEX_SIZE, 60, shape_2d_fvf_tag, triangle_fan_primitive_tag> {
 public:
  oval(const float x, const float y, const float rx, const float ry) : drawable_base(init_vertex(x, y, rx, ry)) {}

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float rx, const float ry) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_OVAL_VERTEX_SIZE, NGY313_OVAL_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }
};

#undef NGY313_OVAL_VERTEX_ELEM_GEN

#undef NGY313_OVAL_VERTEX_SIZE

#define NGY313_LINE_OVAL_VERTEX_SIZE 60

#define NGY313_LINE_OVAL_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(detail::line_vertex_radian<line_oval, n>::value) * rx,\
  y + std::sin(detail::line_vertex_radian<line_oval, n>::value) * ry,\
  0.f,\
  1.f}, 0xFFFFFFFF},

class line_oval : public drawable_base<line_oval, 
                                       NGY313_LINE_OVAL_VERTEX_SIZE,
                                       59,
                                       shape_2d_fvf_tag, 
                                       line_strip_primitive_tag> {
 public:
  line_oval(const float x, const float y, const float rx, const float ry)
      : drawable_base(init_vertex(x, y, rx, ry)) {}

 private:
  static vertex_array_type init_vertex(const float x, const float y, const float rx, const float ry) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_OVAL_VERTEX_SIZE, NGY313_LINE_OVAL_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }
};

#undef NGY313_LINE_OVAL_VERTEX_ELEM_GEN

#undef NGY313_LINE_OVAL_VERTEX_SIZE
}
