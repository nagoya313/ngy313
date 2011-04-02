#ifndef NGY313_GRAPHIC_DETAIL_LINUX_TEXTURE_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_TEXTURE_HPP_
#include <type_traits>
#include <boost/noncopyable.hpp>
#include <GL/gl.h>
#include <ngy313/graphic/detail/linux/graphic_device.hpp>

namespace ngy313 { namespace graphic { namespace detail {
// g++のunique_ptr実装が完全になったらハンドルラッパーを書いてこれは消す
class texture_handle : private boost::noncopyable {
 public:
  explicit texture_handle(const GLuint handle, graphic_device &device) : handle_(handle), flag_(true), device_(device) {}

  texture_handle(texture_handle &&rhs) : handle_(rhs.handle_), flag_(true), device_(rhs.device_) {
    rhs.flag_ = false;
  }
 
  ~texture_handle() {
    device_.begin_scene();
    if (flag_) {
      glDeleteTextures(1, &handle_);
    }
    device_.end_scene();
  }
 
  GLuint get() const {
    return handle_;
  }
 
 private:
  const GLuint handle_;
  bool flag_;
  graphic_device &device_;
};

class texture_access {
 public:
  template <typename Image>
  static const texture_handle &texture1(const Image &image) {
    return image.texture1();
  }
};

class texture_core_access {
 public:
  template <typename Texture>
  static const texture_handle &texture1(const Texture &tex) {
    return tex.texture1();
  }
};



template <typename Drawable>
typename std::enable_if<std::is_same<tex_t<1>, typename drawable_switch_element<Drawable>::type>::value>::type
    set_texture(const Drawable &drawable) {
  //glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture_core_access::texture1(ngy313::graphic::texture_access::texture1(drawable)).get());
  //glEnable(GL_TEXTURE_2D);
}

template <typename Drawable>
typename std::enable_if<std::is_same<boost::mpl::void_, typename drawable_switch_element<Drawable>::type>::value>::type
    set_texture(const Drawable &) {
}
}}}

#endif
