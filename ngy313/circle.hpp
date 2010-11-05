#pragma once
#include <cmath>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <boost/preprocessor/inc.hpp>
#include <boost/preprocessor/arithmetic/dec.hpp>
#include <pstade/oven/make_range.hpp>
#include "drawable_adaptor.hpp"
#include "detail/radian.hpp"

namespace ngy313 {
#define NGY313_CIRCLE_VERTEX_SIZE 62

#define NGY313_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(detail::vertex_radian<circle, n>::value) * r,\
  y + std::sin(detail::vertex_radian<circle, n>::value) * r,\
  0.f,\
  1.f}, 0xFFFFFFFF},

class circle
    : public drawable_adaptor<circle, 
                              NGY313_CIRCLE_VERTEX_SIZE, 
                              60, 
                              make_drawable_tag<dimension2_fvf_tag, 
                                                diffuse_fvf_tag, 
                                                triangle_fan_primitive_tag>> {
 public:
  circle(const float x, const float y, const float r)
      : vertex_(init_vertex(x, y, r)) {}

  vertex_range_type vertex() const {
    return pstade::oven::make_range(vertex_.begin(), vertex_.end());
  }

 private:
  static vertex_array_type init_vertex(const float x, 
                                       const float y,
                                       const float r) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      BOOST_PP_REPEAT_FROM_TO(
          1, 
          BOOST_PP_DEC(BOOST_PP_INC(NGY313_CIRCLE_VERTEX_SIZE)),
          NGY313_CIRCLE_VERTEX_ELEM_GEN, 
          _)
    }};
    return vertex;
  }

  const vertex_array_type vertex_;
};

#undef NGY313_CIRCLE_VERTEX_ELEM_GEN

#undef NGY313_CIRCLE_VERTEX_SIZE
}