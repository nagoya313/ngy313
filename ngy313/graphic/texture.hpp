#ifndef NGY313_GRAPHIC_TEXTURE_HPP_
#define NGY313_GRAPHIC_TEXTURE_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/texture.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/texture.hpp>
#endif
#include <ngy313/graphic/texture_access.hpp>

namespace ngy313 { namespace graphic {
struct texture_tag {};

class texture : private boost::noncopyable {
 public:
  typedef texture texture_type;

  template <typename Image>
  explicit texture(const Image &img) : texture1_(detail::texture_core_access::texture1(img)), 
                                       width_(img.width()),
                                       height_(img.height()) {}

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

 private:
  const detail::texture_handle &texture1() const {
    return texture1_;
  }

  const detail::texture_handle &texture1_;
  const int width_;
  const int height_;

  friend class detail::texture_core_access;
};

/*
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
  const detail::texture_handle &texture1_;
  const detail::texture_handle &texture2_;

  friend class detail::texture_core_access;
};*/
}}

#endif
