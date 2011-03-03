#pragma once
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/utility/if_cc.hpp>

namespace ngy313 { namespace graphic {
// à¯êîÇ™ÉxÉNÉgÉãÇ…Ç»ÇÈÇÃÇÕ{}Ç≈èâä˙âªÇ≈Ç´ÇÈÇÊÇ§Ç…Ç»Ç¡ÇƒÇ©ÇÁ
template <bool Filled>
class box_base : public drawable<box_base<Filled>, 
                                 utility::if_cc<Filled, std::size_t, 4, 5>::value,
                                 utility::if_cc<Filled, std::uint32_t, 2, 4>::value,
                                 shape_2d_fvf_tag, 
                                 typename boost::mpl::if_c<Filled,
                                                           triangle_strip_primitive_tag,
                                                           line_strip_primitive_tag>::type> {
 public:
  box_base(const float x, const float y, const float width, const float height)
      : x_(x), y_(y), width_(width), height_(height) {}

  float width() const {
    return width_;
  }

  float height() const {
    return height_;
  }

 private:
  vertex_array_type vertex() const {
    return vertex_<Filled>();
  }

  template <bool Fill>
  vertex_array_type vertex_(typename std::enable_if<Fill>::type * = nullptr) const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x_, y_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_ + width_, y_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_, y_ + height_), diffuse_t(0xFFFFFFFF)),
      vertex_type(rhw_position_t(x_ + width_, y_ + height_), diffuse_t(0xFFFFFFFF))
    }};
    return vertex;
  }

  template <bool Fill>
  vertex_array_type vertex_(typename std::enable_if<!Fill>::type * = nullptr) const {
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
