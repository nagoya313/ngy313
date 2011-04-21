#ifndef NGY313_GRAPHIC_LINE_HPP_
#define NGY313_GRAPHIC_LINE_HPP_
#include <cstdint>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
class line : public drawable<line, 2, 2, shape_2d_fvf_tag, line_list_primitive_tag> {
 public:
  line(const float x1, const float y1, const float x2, const float y2, const std::uint32_t diffuse)
      : x1_(x1), y1_(y1), x2_(x2), y2_(y2), color_(diffuse) {}

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

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x1_, y1_), diffuse_t(color_)),
      vertex_type(rhw_position_t(x2_, y2_), diffuse_t(color_))
    }};
    return vertex;
  }

  float x1_;
  float y1_;
  float x2_;
  float y2_;
  std::uint32_t color_;

  friend class drawable_access;
};
}}

#endif
