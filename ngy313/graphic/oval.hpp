#pragma once
#include <cmath>
#include <boost/preprocessor/repeat_from_to.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/radian.hpp>
#include <ngy313/utility/if_cc.hpp>

namespace ngy313 { namespace graphic {
#define NGY313_OVAL_VERTEX_SIZE 62

#define NGY313_OVAL_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(vertex_radian<oval, n>::value) * rx,\
  y + std::sin(vertex_radian<oval, n>::value) * ry,\
  0.f,\
  1.f}, 0xFFFFFFFF},

#define NGY313_LINE_OVAL_VERTEX_SIZE 60

#define NGY313_LINE_OVAL_VERTEX_ELEM_GEN(z, n, data)\
{{x + std::cos(line_vertex_radian<line_oval, n>::value) * rx,\
  y + std::sin(line_vertex_radian<line_oval, n>::value) * ry,\
  0.f,\
  1.f}, 0xFFFFFFFF},

template <bool Filled>
class oval_base : public drawable<oval_base<Filled>, 
                                  utility::if_cc<Filled, std::size_t, 62, 60>::value,
                                  utility::if_cc<Filled, std::uint32_t, 60, 59>::value,
                                  shape_2d_fvf_tag, 
                                  typename boost::mpl::if_c<Filled,
                                                            triangle_fan_primitive_tag,
                                                            line_strip_primitive_tag>::type> {
 public:
  oval_base(const float x, const float y, const float rx, const float ry)
      : vertex_(init_vertex<Filled>(x, y, rx, ry)) {}

  // –¢ŽÀ‘•
  float x() const {
    return 0.f;
  }

  // –¢ŽÀ‘•
  float y() const {
    return 0.f;
  }

  // –¢ŽÀ‘•
  float rx() const {
    return 0.f;
  }

  // –¢ŽÀ‘•
  float ry() const {
    return 0.f;
  }

 private:
  vertex_array_type vertex() const {
    return vertex_;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x,
                                       const float y,
                                       const float rx,
                                       const float ry,
                                       typename std::enable_if<Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      {{x, y, 0.f, 1.f}, 0xFFFFFFFF},
      BOOST_PP_REPEAT_FROM_TO(1, NGY313_OVAL_VERTEX_SIZE, NGY313_OVAL_VERTEX_ELEM_GEN, _)
    }};
    return vertex;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x,
                                       const float y, 
                                       const float rx,
                                       const float ry,
                                       typename std::enable_if<!Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      BOOST_PP_REPEAT(NGY313_LINE_OVAL_VERTEX_SIZE, NGY313_LINE_OVAL_VERTEX_ELEM_GEN, _)
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