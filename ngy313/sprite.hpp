#ifndef NGY313_SPRITE_HPP_
#define NGY313_SPRITE_HPP_

#include <memory>
#include <ngy313/drawable_traits.hpp>
#include <ngy313/texture.hpp>
#include <ngy313/vector.hpp>
#include <ngy313/detail/image.hpp>

namespace ngy313 {
class sprite : public drawable_traits<sprite,
                                      4,
                                      2,
                                      image_2d_fvf_tag,
                                      triangle_strip_primitive_tag> {
 public:
  template <typename Image>
  explicit sprite(const Image &image)
      : image_(image.get_image()), vertex_(init(image_->get_texture())) {}

  vertex_array_type vertex() const {
    return vertex_;
  }

  const texture &texture1() const {
    return image_->get_texture();
  }
 
 private:
  static vertex_array_type init(const texture &tex) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)),
      		        texture_t<1>(vector2(0.f, 0.f))),
      vertex_type(rhw_position_t(
                      vector2(static_cast<float>(tex.width()), 0.f)),
      		        texture_t<1>(vector2(1.f, 0.f))),
      vertex_type(rhw_position_t(
                      vector2(0.f, static_cast<float>(tex.height()))),
      		        texture_t<1>(vector2(0.f, 1.f))),
      vertex_type(rhw_position_t(
                  vector2(static_cast<float>(tex.width()),
                          static_cast<float>(tex.height()))),
      		        texture_t<1>(vector2(1.f, 1.f)))
     }};
    return vertex;
   }

  std::shared_ptr<detail::image_base<texture>> image_;
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
      : image_(image.get_image()), vertex_(init(image_->get_texture())) {}

  vertex_array_type vertex() const {
    return vertex_;
  }

  const texture &texture1() const {
    return image_->get_texture();
  }
 
 private:
  static vertex_array_type init(const texture &tex) {
    const vertex_array_type vertex = {{
      vertex_type(rhw_position_t(vector2(0.f, 0.f)),
      		        diffuse_t(),
      		        texture_t<1>(vector2(0.f, 0.f))),
      vertex_type(rhw_position_t(
                      vector2(static_cast<float>(tex.width()), 0.f)),
      		        diffuse_t(),
      		        texture_t<1>(vector2(1.f, 0.f))),
      vertex_type(rhw_position_t(
                      vector2(0.f, static_cast<float>(tex.height()))),
      		        diffuse_t(),
      		        texture_t<1>(vector2(0.f, 1.f))),
      vertex_type(rhw_position_t(
                      vector2(static_cast<float>(tex.width()),
                              static_cast<float>(tex.height()))),
      		        diffuse_t(),
      		        texture_t<1>(vector2(1.f, 1.f)))
    }};
    return vertex;
  }

  std::shared_ptr<detail::image_base<texture>> image_;
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
      : vertex_(init(size)), image_(image.get_image()) {}

  vertex_array_type vertex() const {
    return vertex_;
  }
  
  const texture &texture1() const {
    return image_->get_texture();
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
  std::shared_ptr<detail::image_base<texture>> image_;
};

class bright_size_sprite
    : public drawable_traits<bright_size_sprite,
                             4,
                             2,
                             bright_image_2d_fvf_tag,
                             triangle_strip_primitive_tag> {
 public:
  template <typename Image>
  explicit bright_size_sprite(const vector2 &size, const Image &image)
      : vertex_(init(size)), image_(image.get_image()) {}

  vertex_array_type vertex() const {
    return vertex_;
  }
  
  const texture &texture1() const {
    return image_->get_texture();
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
  std::shared_ptr<detail::image_base<texture>> image_;
};
}

#endif
