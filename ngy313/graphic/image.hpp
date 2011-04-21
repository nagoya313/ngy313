#ifndef NGY313_GRAPHIC_IMAGE_HPP_
#define NGY313_GRAPHIC_IMAGE_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/image_loader.hpp>
#include <ngy313/graphic/detail/windows/texture.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/image_loader.hpp>
#include <ngy313/graphic/detail/linux/texture.hpp>
#endif
#include <ngy313/graphic/detail/texture.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic {
const struct alpha_png_image_loader_t {
  std::tuple<detail::texture_handle, int, int> operator()(const utility::string_piece &file_name) const {
    return detail::create_texture_from_alpha_png_file(detail::device().device(), file_name);
  }
} alpha_png_image_loader = {};

struct non_alpha_png_image_loader_t {
  std::tuple<detail::texture_handle, int, int> operator()(const utility::string_piece &file_name) const {
    return detail::create_texture_from_non_alpha_png_file(detail::device().device(), file_name);
  }
} non_alpha_png_image_loader = {};

struct jpeg_image_loader_t {
  std::tuple<detail::texture_handle, int, int> operator()(const utility::string_piece &file_name) const {
    return detail::create_texture_from_jpeg_file(detail::device().device(), file_name);
  }
} jpeg_image_loader = {};

class image : private boost::noncopyable {
 public:
  template <typename Loader>
  image(const utility::string_piece &file_name, const Loader &loader) : texture_(file_name, loader) {}

  int width() const {
    return texture_.width();
  }

  int height() const {
    return texture_.height();
  }

 private:
  const detail::texture_handle &texture1() const {
    return texture_.texture();
  }

  const detail::texture_type texture_;

  friend class detail::texture_core_access;
};
}}

#endif
