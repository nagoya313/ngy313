#pragma once
#include <cmath>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/radian.hpp>

namespace ngy313 { namespace graphic {
#define NGY313_OVAL_VERTEX_SIZE 62

#define NGY313_OVAL_VERTEX_ELEM_GEN(z, n, data)\
vertex_type(rhw_position_t(x + std::cos(vertex_radian<data, n>::value) * rx,\
  y + std::sin(vertex_radian<data, n>::value) * ry), diffuse_t(0xFFFFFFFF)),

#define NGY313_LINE_OVAL_VERTEX_SIZE 60

#define NGY313_LINE_OVAL_VERTEX_ELEM_GEN(z, n, data)\
vertex_type(rhw_position_t(x + std::cos(line_vertex_radian<data, n>::value) * rx,\
  y + std::sin(line_vertex_radian<data, n>::value) * ry), diffuse_t(0xFFFFFFFF)),

template <bool Filled>
class oval_base 
    : public boost::mpl::if_c<Filled,
                              drawable<oval_base<Filled>, 62, 60, shape_2d_fvf_tag, triangle_fan_primitive_tag>,
                              drawable<oval_base<Filled>, 60, 59, shape_2d_fvf_tag, line_strip_primitive_tag>>::type {
 typedef typename oval_base::drawable base;
                           
 public:
  typedef typename base::vertex_type vertex_type;
  typedef typename base::vertex_array_type vertex_array_type;
  oval_base(const float x, const float y, const float rx, const float ry)
      : vertex_(init_vertex<Filled>(x, y, rx, ry)) {}

 private:
  vertex_array_type vertex() const {
    return vertex_;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x,
                                       const float y,
                                       const float rx,
                                       const float ry,
                                       typename std::enable_if<Fill>::type * = 0) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x, y), diffuse_t(0xFFFFFFFF)),
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_OVAL_VERTEX_SIZE, NGY313_OVAL_VERTEX_ELEM_GEN, oval_base)
    }};
    return vertex;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x,
                                       const float y, 
                                       const float rx,
                                       const float ry,
                                       typename std::enable_if<!Fill>::type * = 0) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_OVAL_VERTEX_SIZE, NGY313_LINE_OVAL_VERTEX_ELEM_GEN, oval_base)
    }};
    return vertex;
  }

  const vertex_array_type vertex_;

  friend class drawable_access;
};

#undef NGY313_OVAL_VERTEX_ELEM_GEN
#undef NGY313_OVAL_VERTEX_SIZE
#undef NGY313_LINE_OVAL_VERTEX_ELEM_GEN
#undef NGY313_LINE_OVAL_VERTEX_SIZE

typedef oval_base<true> oval;
typedef oval_base<false> line_oval;
}}
