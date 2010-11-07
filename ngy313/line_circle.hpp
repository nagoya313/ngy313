#pragma once
#include <cmath>
#include <boost/preprocessor/repeat.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <pstade/oven/make_range.hpp>
#include "detail/radian.hpp"
#include "drawable_adaptor.hpp"

namespace ngy313 {
#define NGY313_LINE_CIRCLE_VERTEX_SIZE 60

#define NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(detail::line_vertex_radian<line_circle, n>::value) * r,\
  y + std::sin(detail::line_vertex_radian<line_circle, n>::value) * r,\
  0.f,\
  1.f}, 0xFFFFFFFF},

class line_circle
    : public drawable_adaptor<line_circle, 
                              NGY313_LINE_CIRCLE_VERTEX_SIZE, 
                              59,
                              make_drawable_tag<dimension2_fvf_tag, 
                                                diffuse_fvf_tag, 
                                                line_strip_primitive_tag>> {
 public:
  line_circle(const float x, const float y, const float r)
      : drawable_adaptor(init_vertex(x, y, r)) {}

 private:
  static vertex_array_type init_vertex(const float x, 
                                       const float y, 
                                       const float r) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(BOOST_PP_DEC(BOOST_PP_INC(NGY313_LINE_CIRCLE_VERTEX_SIZE)),
                      NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN, 
                      _)
    }};
    return vertex;
  }
};

#undef NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN

#undef NGY313_LINE_CIRCLE_VERTEX_SIZE
}