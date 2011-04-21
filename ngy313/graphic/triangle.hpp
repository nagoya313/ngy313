#ifndef NGY313_GRAPHIC_TRIANGLE_HPP_
#define NGY313_GRAPHIC_TRIANGLE_HPP_
#include <cstdint>
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
  
  triangle_base(const float x1, const float y1, const float x2, const float y2, const float x3, const float y3, const std::uint32_t diffuse) 
      : x1_(x1), y1_(y1), x2_(x2), y2_(y2), x3_(x3), y3_(y3), color_(diffuse) {}

  float x1() const {
    return x1_;
  }

  float y1() const {
    return y1_;
  }

  float x2() const {
    return x2_;
  }

  float y2() const {
    return y2_;
  }

  float x3() const {
    return x3_;
  }

  float y3() const {
    return y3_;
  }

 private:
  vertex_array_type vertex() const {
    return vertex_<Filled>();
  }

  template <bool Fill>
  vertex_array_type vertex_(typename std::enable_if<Fill>::type * = 0) const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x1_, y1_), diffuse_t(color_)),
      vertex_type(rhw_position_t(x2_, y2_), diffuse_t(color_)),
      vertex_type(rhw_position_t(x3_, y3_), diffuse_t(color_))
    }};
    return vertex;
  }

  template <bool Fill>
  vertex_array_type vertex_(typename std::enable_if<!Fill>::type * = 0) const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x1_, y1_), diffuse_t(color_)),
      vertex_type(rhw_position_t(x2_, y2_), diffuse_t(color_)),
      vertex_type(rhw_position_t(x3_, y3_), diffuse_t(color_)),
      vertex_type(rhw_position_t(x1_, y1_), diffuse_t(color_))
    }};
    return vertex;
  }

  float x1_;
  float y1_;
  float x2_; 
  float y2_; 
  float x3_; 
  float y3_;
  std::uint32_t color_;

  friend class drawable_access;
};

typedef triangle_base<true> triangle;
typedef triangle_base<false> line_triangle;
}}

#endif
