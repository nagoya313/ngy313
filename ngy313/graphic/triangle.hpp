#ifndef NGY313_GRAPHIC_TRIANGLE_HPP_
#define NGY313_GRAPHIC_TRIANGLE_HPP_
#include <boost/mpl/if.hpp>
#include <boost/mpl/size_t.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>

namespace ngy313 { namespace graphic {
template <bool Filled>
class triangle_base
   : public boost::mpl::if_c<Filled,
                             drawable<triangle_base<Filled>, 3, 1, shape_2d_fvf_tag, triangle_list_primitive_tag>,
                             drawable<triangle_base<Filled>, 4, 3, shape_2d_fvf_tag, line_strip_primitive_tag>>::type {
  typedef typename triangle_base::drawable base;

 public:
  typedef typename base::vertex_type vertex_type;
  typedef typename base::vertex_array_type vertex_array_type;
  
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
                                       typename std::enable_if<Fill>::type * = 0) {
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
                                       typename std::enable_if<!Fill>::type * = 0) {
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

typedef triangle_base<true> triangle;
typedef triangle_base<false> line_triangle;
}}

#endif

