#ifndef NGY313_TEXTURE_HPP_
#define NGY313_TEXTURE_HPP_

#include <boost/noncopyable.hpp>
#include <ngy313/detail/ngy313.hpp>

#if defined(_WIN32)
#incldue <ngy313/detail/direct3d9_texture.hpp>
#elif defined(__linux__)
#include <ngy313/detail/opengl_texture.hpp>
#endif

namespace ngy313 {
template <typename Texture>
class basic_texture {
 public:
  typedef typename Texture::handle_type handle_type;
  typedef typename Texture::texture_tuple texture_tuple;
  typedef typename Texture::deleter_type deleter_type;

  explicit basic_texture(int width, int height)
      : texture_(detail::main_singleton::instance().graphic(),
      		        width,
      		        height) {}

  template <typename Image>
  explicit basic_texture(const Image &image)
      : texture_(detail::main_singleton::instance().graphic(),
                 image) {}

  int width() const {
    return texture_.width();
  }

  int height() const {
    return texture_.height();
  }

 handle_type handle() const {
    return texture_.handle();
  }

 private:
  Texture texture_;
};

#if defined(_WIN32)
typedef basic_texture<detail::direct3d9_texture> texture;
#elif defined(__linux__)
typedef basic_texture<detail::opengl_texture<detail::graphic_system>> texture;
#endif
}

#endif
