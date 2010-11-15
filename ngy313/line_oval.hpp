#pragma once
#include <cmath>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include "detail/radian.hpp"
#include "drawable_base.hpp"

namespace ngy313 {
#define NGY313_LINE_OVAL_VERTEX_SIZE 60

#define NGY313_LINE_OVAL_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(detail::line_vertex_radian<line_oval, n>::value) * rx,\
  y + std::sin(detail::line_vertex_radian<line_oval, n>::value) * ry,\
  0.f,\
  1.f}, 0xFFFFFFFF},

class line_oval
    : public drawable_base<line_oval, 
                           NGY313_LINE_OVAL_VERTEX_SIZE,
                           59,
                           shape_2d_fvf_tag, 
                           line_strip_primitive_tag> {
 public:
  line_oval(const float x, const float y, const float rx, const float ry)
      : drawable_base(init_vertex(x, y, rx, ry)) {}

 private:
  static vertex_array_type init_vertex(const float x, 
                                       const float y,
                                       const float rx, 
                                       const float ry) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(BOOST_PP_DEC(BOOST_PP_INC(NGY313_LINE_OVAL_VERTEX_SIZE)),
                      NGY313_LINE_OVAL_VERTEX_ELEM_GEN, 
                      _)
    }};
    return vertex;
  }
};

#undef NGY313_LINE_OVAL_VERTEX_ELEM_GEN

#undef NGY313_LINE_OVAL_VERTEX_SIZE
}