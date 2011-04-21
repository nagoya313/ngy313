#ifndef NGY313_GRAPHIC_OVAL_HPP_
#define NGY313_GRAPHIC_OVAL_HPP_
#include <cmath>
#include <cstdint>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/detail/radian.hpp>

namespace ngy313 { namespace graphic {
#define NGY313_OVAL_VERTEX_SIZE 62

#define NGY313_OVAL_VERTEX_ELEM_GEN(z, n, data)\
vertex_type(rhw_position_t(x_ + std::cos(detail::vertex_radian<data, n>::value) * rx_,\
  y_+ std::sin(detail::vertex_radian<data, n>::value) * ry_), diffuse_t(color_)),

#define NGY313_LINE_OVAL_VERTEX_SIZE 60

#define NGY313_LINE_OVAL_VERTEX_ELEM_GEN(z, n, data)\
vertex_type(rhw_position_t(x_ + std::cos(detail::line_vertex_radian<data, n>::value) * rx_,\
  y_ + std::sin(detail::line_vertex_radian<data, n>::value) * ry_), diffuse_t(color_)),

template <bool Filled>
class oval_base 
    : public boost::mpl::if_c<Filled,
                              drawable<oval_base<Filled>, 62, 60, shape_2d_fvf_tag, triangle_fan_primitive_tag>,
                              drawable<oval_base<Filled>, 60, 59, shape_2d_fvf_tag, line_strip_primitive_tag>>::type {
 typedef typename oval_base::drawable base;
                           
 public:
  typedef typename base::vertex_type vertex_type;
  typedef typename base::vertex_array_type vertex_array_type;
  oval_base(const float x, const float y, const float rx, const float ry, const std::uint32_t diffuse)
      : x_(x), y_(y), rx_(rx), ry_(ry), color_(diffuse) {}

  float x() const {
    return x_;
  }

  float y() const {
    return y_;
  }

  float rx() const {
    return rx_;
  }

  float ry() const {
    return ry_;
  }

 private:
  vertex_array_type vertex() const {
    return vertex_<Filled>();
  }

  template <bool Fill>
  vertex_array_type vertex_(typename std::enable_if<Fill>::type * = 0) const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x_, y_), diffuse_t(color_)),
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_OVAL_VERTEX_SIZE, NGY313_OVAL_VERTEX_ELEM_GEN, oval_base)
    }};
    return vertex;
  }

  template <bool Fill>
  vertex_array_type vertex_(typename std::enable_if<!Fill>::type * = 0) const {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_OVAL_VERTEX_SIZE, NGY313_LINE_OVAL_VERTEX_ELEM_GEN, oval_base)
    }};
    return vertex;
  }

  float x_;
  float y_;
  float rx_;
  float ry_;
  std::uint32_t color_;

  friend class drawable_access;
};

#undef NGY313_OVAL_VERTEX_ELEM_GEN
#undef NGY313_OVAL_VERTEX_SIZE
#undef NGY313_LINE_OVAL_VERTEX_ELEM_GEN
#undef NGY313_LINE_OVAL_VERTEX_SIZE

typedef oval_base<true> oval;
typedef oval_base<false> line_oval;
}}

#endif
