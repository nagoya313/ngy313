#ifndef NGY313_GRAPHIC_IMAGE_HPP_
#define NGY313_GRAPHIC_IMAGE_HPP_
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/image_loader.hpp>
#include <ngy313/graphic/detail/windows/texture.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/image_loader.hpp>
#include <ngy313/graphic/detail/linux/texture.hpp>
#endif
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic {
class image {
 public: 
  explicit image(const utility::string_piece &file_name) : texture_(detail::init_texture_key(file_name.string())) {}

  int width() const {
    return texture_.get().width();
  }

  int height() const {
    return texture_.get().height();
  }

 private:
  const detail::texture_handle &texture1() const {
    return texture_.get().texture();
  }

  const detail::texture_type texture_;

  friend class detail::texture_access;
};
}}

#endif
