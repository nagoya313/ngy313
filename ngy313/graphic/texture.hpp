#pragma once
#include <ngy313/graphic/detail/texture.hpp>

namespace ngy313 { namespace graphic {
class texture {
 public:
  typedef texture texture_type;

  template <typename Image>
  explicit texture(const Image &img) : texture1_(detail::texture_access::texture1(img)), 
                                       width_(img.width()),
                                       height_(img.height()) {}

  float width() const {
    return width_;
  }

  float height() const {
    return height_;
  }

 private:
  const detail::texture_handle &texture1() const {
    return texture1_;
  }

  const detail::texture_handle texture1_;
  const float width_;
  const float height_;

  friend class detail::texture_access;
  friend class detail::texture_core_access;
};

class multi_texture {
 public:
  typedef multi_texture multi_texture_type;

  template <typename Image1, typename Image2>
  multi_texture(const Image1 &img1, const Image2 &img2) 
      : texture1_(detail::texture_access::texture(img1)), texture2_(detail::texture_access::texture(img2)) {}

  const detail::texture_handle &texture1() const {
    return texture1_;
  }

  const detail::texture_handle &texture2() const {
    return texture2_;
  }

 private:
  const detail::texture_handle texture1_;
  const detail::texture_handle texture2_;

  friend class detail::texture_core_access;
};
}}