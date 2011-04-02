#ifndef NGY313_GRAPHIC_SPRITE_HPP_
#define NGY313_GRAPHIC_SPRITE_HPP_
#include <ngy313/graphic/texture.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/graphic/fvf_tag.hpp>
#include <ngy313/graphic/primitive_tag.hpp>

namespace ngy313 { namespace graphic {
class sprite : public drawable<sprite, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  template <typename Image>
  sprite(const float x, const float y, const Image &image) : texture_(image), x_(x), y_(y) {}

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x_, y_), diffuse_t(0xFFFFFFFF), tex_t<1>(0.f, 0.f)),
      vertex_type(rhw_position_t(x_ + texture_.width(), y_), diffuse_t(0xFFFFFFFF), tex_t<1>(1.f, 0.f)),
      vertex_type(rhw_position_t(x_, y_ + texture_.height()), diffuse_t(0xFFFFFFFF), tex_t<1>(0.f, 1.f)),
      vertex_type(rhw_position_t(x_ + texture_.width(), y_ + texture_.height()), diffuse_t(0xFFFFFFFF), tex_t<1>(1.f, 1.f))
    }};
    return vertex;
  }

  const texture &texture1() const {
    return texture_;
  }

  const texture texture_;
  const float x_;
  const float y_;

  friend class drawable_access;
  friend class texture_access;
};

class size_sprite : public drawable<size_sprite, 4, 2, image_2d_fvf_tag, triangle_strip_primitive_tag> {
 public:
  template <typename Image>
  size_sprite(const float x, const float y, const float width, const float height, const Image &image)
      : texture_(image), x_(x), y_(y), width_(width), height_(height) {}

 private:
  vertex_array_type vertex() const {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(x_, y_), diffuse_t(0xFFFFFFFF), tex_t<1>(0.f, 0.f)),
      vertex_type(rhw_position_t(x_ + width_, y_), diffuse_t(0xFFFFFFFF), tex_t<1>(1.f, 0.f)),
      vertex_type(rhw_position_t(x_, y_ + height_), diffuse_t(0xFFFFFFFF), tex_t<1>(0.f, 1.f)),
      vertex_type(rhw_position_t(x_ + width_, y_ + height_), diffuse_t(0xFFFFFFFF), tex_t<1>(1.f, 1.f))
    }};
    return vertex;
  }
  
  const texture &texture1() const {
    return texture_;
  }
  
  const texture texture_;
  const float x_;
  const float y_;
  const float width_;
  const float height_;

  friend class drawable_access;
  friend class texture_access;
};
}}

#endif
