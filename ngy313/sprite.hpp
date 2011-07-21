#ifndef NGY313_SPRITE_HPP_
#define NGY313_SPRITE_HPP_

#include <ngy313/drawable_traits.hpp>
#include <ngy313/texture.hpp>
#include <ngy313/vector.hpp>

namespace ngy313 {
class sprite : public drawable_traits<sprite,
                                           4,
                                           2,
                                      image_2d_fvf_tag,
                                      triangle_strip_primitive_tag> {
 public:
  template <typename Image>
  explicit sprite(const Image &image)
      : texture_(image.get_texture()), vertex_(init(texture_)) {}

  vertex_array_type vertex() const {
    return vertex_;
  }

  const texture &texture1() const {
    return texture_;
  }
 
 private:
  static vertex_array_type init(const texture &tex) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)),
      		         texture_t<1>(vector2(0.f, 0.f))),
      vertex_type(rhw_position_t(vector2(static_cast<float>(tex.width()), 0.f)),
      		         texture_t<1>(vector2(1.f, 0.f))),
      vertex_type(rhw_position_t(vector2(0.f, static_cast<float>(tex.height()))),
      		         texture_t<1>(vector2(0.f, 1.f))),
      vertex_type(rhw_position_t(vector2(static_cast<float>(tex.width()), static_cast<float>(tex.height()))),
      		         texture_t<1>(vector2(1.f, 1.f)))
     }};
    return vertex;
   }

  texture texture_;
  vertex_array_type vertex_;
};

class bright_sprite : public drawable_traits<bright_sprite,
                                             4,
                                             2,
                                             bright_image_2d_fvf_tag,
                                             triangle_strip_primitive_tag> {
 public:
  template <typename Image>
  explicit bright_sprite(const Image &image)
      : texture_(image), vertex_(init(texture_)) {}

  vertex_array_type vertex() const {
    return vertex_;
  }

  const texture &texture1() const {
    return texture_;
  }
 
 private:
  static vertex_array_type init(const texture &tex) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)),
      		         diffuse_t(),
      		         texture_t<1>(vector2(0.f, 0.f))),
      vertex_type(rhw_position_t(vector2(static_cast<float>(tex.width()), 0.f)),
      		         diffuse_t(),
      		         texture_t<1>(vector2(1.f, 0.f))),
      vertex_type(rhw_position_t(vector2(0.f, static_cast<float>(tex.height()))),
      		         diffuse_t(),
      		         texture_t<1>(vector2(0.f, 1.f))),
      vertex_type(rhw_position_t(vector2(static_cast<float>(tex.width()), static_cast<float>(tex.height()))),
      		         diffuse_t(),
      		         texture_t<1>(vector2(1.f, 1.f)))
    }};
    return vertex;
  }

  texture texture_;
  vertex_array_type vertex_;
};

class size_sprite : public drawable_traits<size_sprite,
                                           4,
                                           2,
                                           image_2d_fvf_tag,
                                           triangle_strip_primitive_tag> {
 public:
  template <typename Image>
  explicit size_sprite(const vector2 &size, const Image &image)
      : vertex_(init(size)), texture_(image) {}

  vertex_array_type vertex() const {
    return vertex_;
  }
  
  const texture &texture1() const {
    return texture_;
  }
  
 private:
  static vertex_array_type init(const vector2 &size) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)),
      		         texture_t<1>(vector2(0.f, 0.f))),
      vertex_type(rhw_position_t(vector2(size.get_x(), 0.f)),
      		         texture_t<1>(vector2(1.f, 0.f))),
      vertex_type(rhw_position_t(vector2(0.f, size.get_y())),
      		         texture_t<1>(vector2(0.f, 1.f))),
      vertex_type(rhw_position_t(vector2(size.get_x(), size.get_y())),
      		         texture_t<1>(vector2(1.f, 1.f)))
     }};
    return vertex;
   }

  vertex_array_type vertex_;
  texture texture_;
};

class bright_size_sprite : public drawable_traits<bright_size_sprite,
                                                  4,
                                                  2,
                                                  bright_image_2d_fvf_tag,
                                                  triangle_strip_primitive_tag> {
 public:
  template <typename Image>
  explicit bright_size_sprite(const vector2 &size,
                              const Image &image)
      : vertex_(init(size)), texture_(image) {}

  vertex_array_type vertex() const {
    return vertex_;
  }
  
  const texture &texture1() const {
    return texture_;
  }
  
 private:
  static vertex_array_type init(const vector2 &size) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)),
      		         diffuse_t(),
      		         texture_t<1>(vector2(0.f, 0.f))),
      vertex_type(rhw_position_t(vector2(size.get_x(), 0.f)),
      		         diffuse_t(),
      		         texture_t<1>(vector2(1.f, 0.f))),
      vertex_type(rhw_position_t(vector2(0.f, size.get_y())),
      		         diffuse_t(),
      		         texture_t<1>(vector2(0.f, 1.f))),
      vertex_type(rhw_position_t(vector2(size.get_x(), size.get_y())),
      		         diffuse_t(),
      		         texture_t<1>(vector2(1.f, 1.f)))
     }};
    return vertex;
   }

  vertex_array_type vertex_;
  texture texture_;
};
}

#endif
