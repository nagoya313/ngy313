#ifndef NGY313_IMAGE_HPP_
#define NGY313_IMAGE_HPP_

#include <ngy313/texture.hpp>
#include <ngy313/string_wrap.hpp>
#include <ngy313/detail/init_base.hpp>

#if defined(_WIN32)
#include <ngy313/detail/direct3d9_image.hpp>
#elif defined(__linux__)
#include <ngy313/detail/gtkmm_image.hpp>
#endif

namespace ngy313 {
template <typename Image>
class basic_image : detail::init_base {
 public:
  explicit basic_image(const string_wrap &file_name)
      : tuxture_(Image(file_name)) {}

  int width() const {
    return tuxture_.width();
  }

  int height() const {
    return tuxture_.height();
  }

  const texture &get_texture() const {
    return tuxture_;
  }

 private:
  texture tuxture_;
};

#if defined(_WIN32)
typedef basic_image<detail::direct3d9_image<texture>> image;
#elif defined(__linux__)
typedef basic_image<detail::gtkmm_image<texture>> image;
#endif

}

#endif
