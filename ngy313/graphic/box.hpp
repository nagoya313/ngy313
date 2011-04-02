#pragma once
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>

namespace ngy313 { namespace graphic {
// à¯êîÇ™ÉxÉNÉgÉãÇ…Ç»ÇÈÇÃÇÕ{}Ç≈èâä˙âªÇ≈Ç´ÇÈÇÊÇ§Ç…Ç»Ç¡ÇƒÇ©ÇÁ
template <bool Filled>
class box_base 
    : public boost::mpl::if_c<Filled,
                              drawable<box_base<Filled>, 4, 5, shape_2d_fvf_tag, triangle_strip_primitive_tag>,
                              drawable<box_base<Filled>, 2, 4, shape_2d_fvf_tag, line_strip_primitive_tag>>::type {
  typedef typename box_base::drawable base;
                                                           
 public:
  typedef typename base::vertex_type vertex_type;
  typedef typename base::vertex_array_type vertex_array_type;
  
  box_base(const float x, const float y, const float width, const float height)
      : x_(x), y_(y), width_(width), height_(height) {}

  float width() const {
    return width_;
  }

  float height() const {
    return height_;
  }

 private:
  typename base::vertex_array_type vertex() const {
    return vertex_<Filled>();
  }

  template <bool Fill>
  vertex_array_type vertex_(typename std::enable_if<Fill>::type * = 0) const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x_, y_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_ + width_, y_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_, y_ + height_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_ + width_, y_ + height_), diffuse_t(0xFFFFFFFF))
    }};
    return vertex;
  }

  template <bool Fill>
  vertex_array_type vertex_(typename std::enable_if<!Fill>::type * = 0) const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x_, y_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_ + width_, y_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_ + width_, y_ + height_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_, y_ + height_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_, y_), diffuse_t(0xFFFFFFFF))
    }};
    return vertex;
  }

  float x_;
  float y_;
  float width_;
  float height_;

  friend class drawable_access;
};

typedef box_base<true> box;
typedef box_base<false> line_box;
}}
