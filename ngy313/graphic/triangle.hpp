#pragma once
#include <boost/mpl/if.hpp>
#include <boost/mpl/size_t.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/utility/if_cc.hpp>

namespace ngy313 { namespace graphic {
#pragma warning(disable: 4512)

template <bool Filled>
class triangle_base 
    : public drawable<triangle_base<Filled>, 
                      utility::if_cc<Filled, std::size_t, 3, 4>::value,
                      utility::if_cc<Filled, std::uint32_t, 1, 3>::value,
                      shape_2d_fvf_tag,
                      typename boost::mpl::if_c<Filled,
                                                triangle_list_primitive_tag,
                                                line_strip_primitive_tag>::type> {
 public:
  triangle_base(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3) 
      : vertex_(init_vertex<Filled>(x1, y1, x2, y2, x3, y3)) {}

 private:
  vertex_array_type vertex() const {
    return vertex_;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x1, 
                                       const float y1,
                                       const float x2, 
                                       const float y2, 
                                       const float x3, 
                                       const float y3,
                                       typename std::enable_if<Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x1, y1), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x2, y2), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x3, y3), diffuse_t(0xFFFFFFFF))
    }};
    return vertex;
  }

  template <bool Fill>
  static vertex_array_type init_vertex(const float x1, 
                                       const float y1,
                                       const float x2, 
                                       const float y2, 
                                       const float x3, 
                                       const float y3,
                                       typename std::enable_if<!Fill>::type * = nullptr) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x1, y1), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x2, y2), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x3, y3), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x1, y1), diffuse_t(0xFFFFFFFF))
    }};
    return vertex;
  }

  const vertex_array_type vertex_;

  friend class drawable_access;
};

#pragma warning(default: 4512)

typedef triangle_base<true> triangle;
typedef triangle_base<false> line_triangle;
}}
