#pragma once
#include <cmath>
#include <boost/preprocessor/repeat_from_to.hpp>
#include "detail/radian.hpp"
#include "drawable_base.hpp"

namespace ngy313 {
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
}