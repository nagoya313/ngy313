#pragma once
#include <cmath>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/radian.hpp>
#include <ngy313/utility/if_cc.hpp>

namespace ngy313 { namespace graphic {
#define NGY313_CIRCLE_VERTEX_SIZE 62

#define NGY313_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(vertex_radian<circle, n>::value) * r,\
  y + std::sin(vertex_radian<circle, n>::value) * r,\
  0.f,\
  1.f}, 0xFFFFFFFF},

#define NGY313_LINE_CIRCLE_VERTEX_SIZE 60

#define NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(line_vertex_radian<line_circle, n>::value) * r,\
  y + std::sin(line_vertex_radian<line_circle, n>::value) * r,\
  0.f,\
  1.f}, 0xFFFFFFFF},

template <bool Filled>
class circle_base : public drawable<circle_base<Filled>, 
                                    utility::if_cc<Filled, std::size_t, 62, 60>::value,
                                    utility::if_cc<Filled, std::uint32_t, 60, 59>::value,
                                    shape_2d_fvf_tag, 
                                    typename boost::mpl::if_c<Filled,
                                                              triangle_fan_primitive_tag,
                                                              line_strip_primitive_tag>::type> {
 public:
  circle_base(const float x, const float y, const float r)
      : vertex_(init_vertex<Filled>(x, y, r)) {}

  // –¢ŽÀ‘•
  float x() const {
    return 0.f;
  }

  // –¢ŽÀ‘•
  float y() const {
    return 0.f;
  }

  // –¢ŽÀ‘•
  float r() const {
    return 0.f;
  }

 private:
  vertex_array_type vertex() const {
    return vertex_;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x,
                                       const float y,
                                       const float r, 
                                       typename std::enable_if<Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_CIRCLE_VERTEX_SIZE, NGY313_CIRCLE_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x,
                                       const float y, 
                                       const float r,
                                       typename std::enable_if<!Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_CIRCLE_VERTEX_SIZE, NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
    return vertex;
  }

  const vertex_array_type vertex_;

  friend class drawable_access;
};

#undef NGY313_CIRCLE_VERTEX_ELEM_GEN
#undef NGY313_CIRCLE_VERTEX_SIZE
#undef NGY313_LINE_CIRCLE_VERTEX_ELEM_GEN
#undef NGY313_LINE_CIRCLE_VERTEX_SIZE

typedef circle_base<true> circle;
typedef circle_base<false> line_circle;
}}