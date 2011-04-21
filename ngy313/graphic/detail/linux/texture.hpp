#ifndef NGY313_GRAPHIC_DETAIL_LINUX_TEXTURE_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_TEXTURE_HPP_
#include <memory>
#include <type_traits>
#include <boost/noncopyable.hpp>
#include <GL/gl.h>
#include <ngy313/graphic/detail/linux/graphic_device.hpp>

namespace ngy313 { namespace graphic { namespace detail {
struct texture_delete {
  explicit texture_delete(device_handle &device) : device_(device) {}
  
  void operator ()(const GLuint * const texture) const {
    device_.begin_scene();
    glDeleteTextures(1, texture);
    device_.end_scene();
    delete texture;
  }
  
 private:
  device_handle &device_;
};

typedef std::unique_ptr<GLuint, texture_delete> texture_handle;

texture_handle create_texture(device_handle &device, const int width, const int height) {
  GLuint *id = new GLuint();
  device.begin_scene();
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glGenTextures(1, id);
  glBindTexture(GL_TEXTURE_2D, *id);
  //gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
  device.end_scene();
  std::cout << *id << std::endl;
  return texture_handle(id, texture_delete(device));
}

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


struct set_texture {
  template <typename Drawable>
  static typename std::enable_if<std::is_same<tex_t<1>, typename drawable_switch_element<Drawable>::type>::value>::type
      set(const Drawable &drawable) {
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, *texture_core_access::texture1(ngy313::graphic::texture_access::texture1(drawable)));
  }

  template <typename Drawable>
  static typename std::enable_if<std::is_same<boost::mpl::void_, typename drawable_switch_element<Drawable>::type>::value>::type
      set(const Drawable &) {
    glDisable(GL_TEXTURE_2D);
  }
};
}}}

#endif
