#pragma once
#include <ngy313/graphic/texture.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>

namespace ngy313 { namespace graphic {
class sprite : public drawable<sprite, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag>, public texture {
 public:
  template <typename Image>
  sprite(const float x, const float y, const Image &image) : texture(image), x_(x), y_(y) {}

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
      {{x_, y_, 0.f, 1.f}, 0xFFFFFFFF, 0.f, 0.f},
      {{x_ + width(), y_, 0.f, 1.f}, 0xFFFFFFFF, 1.f, 0.f},
      {{x_, y_ + height(), 0.f, 1.f}, 0xFFFFFFFF, 0.f, 1.f},
      {{x_ + width(), y_ + height(), 0.f, 1.f}, 0xFFFFFFFF, 1.f, 1.f}
    }};
    return vertex;
  }

  const float x_;
  const float y_;

  friend class drawable_access;
};
}}