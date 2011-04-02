#ifndef NGY313_GRAPHIC_PIXEL_HPP_
#define NGY313_GRAPHIC_PIXEL_HPP_
#include <ngy313/platform.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
class pixel : public drawable<pixel, 1, 1, shape_2d_fvf_tag, point_list_primitive_tag> {
 public:
  pixel(const float x, const float y) : x_(x), y_(y) {}

  float x() const {
    return x_;
  }

  float y() const {
    return y_;
  }

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
//#ifdef NGY313_WINDOWS
      vertex_type(rhw_position_t(x_, y_), diffuse_t(0xFFFFFFFF))
//#else
//#ifdef NGY313_LINUX
  //    vertex_type(diffuse_t(0xFFFFFFFF), rhw_position_t(x_, y_))
//#endif
//#endif
    }};
    return vertex;
  }

  float x_;
  float y_;

  friend class drawable_access;
};
}}

#endif

