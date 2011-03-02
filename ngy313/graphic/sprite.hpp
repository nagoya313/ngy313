#pragma once
#include <ngy313/graphic/texture.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>

namespace ngy313 { namespace graphic {
#pragma warning(disable: 4512)

class sprite : public drawable<sprite, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  template <typename Image>
  sprite(const float x, const float y, const Image &image) : texture_(image), x_(x), y_(y) {}

  const texture &tex() const {
    return texture_;
  }

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
      {{x_, y_, 0.f, 1.f}, 0xFFFFFFFF, 0.f, 0.f},
      {{x_ + texture_.width(), y_, 0.f, 1.f}, 0xFFFFFFFF, 1.f, 0.f},
      {{x_, y_ + texture_.height(), 0.f, 1.f}, 0xFFFFFFFF, 0.f, 1.f},
      {{x_ + texture_.width(), y_ + texture_.height(), 0.f, 1.f}, 0xFFFFFFFF, 1.f, 1.f}
    }};
    return vertex;
  }

  const texture texture_;
  const float x_;
  const float y_;

  friend class drawable_access;
};

class size_sprite : public drawable<size_sprite, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag>, public texture {
 public:
  template <typename Image>
  size_sprite(const float x, const float y, const float width, const float height, const Image &image)
      : texture(image), x_(x), y_(y), width_(width), height_(height) {}

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
      {{x_, y_, 0.f, 1.f}, 0xFFFFFFFF, 0.f, 0.f},
      {{x_ + width_, y_, 0.f, 1.f}, 0xFFFFFFFF, 1.f, 0.f},
      {{x_, y_ + height_, 0.f, 1.f}, 0xFFFFFFFF, 0.f, 1.f},
      {{x_ + width_, y_ + height_, 0.f, 1.f}, 0xFFFFFFFF, 1.f, 1.f}
    }};
    return vertex;
  }

  const float x_;
  const float y_;
  const float width_;
  const float height_;

  friend class drawable_access;
};

#pragma warning(default: 4512)
}}