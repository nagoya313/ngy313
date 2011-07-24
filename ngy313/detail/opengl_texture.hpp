#ifndef NGY313_DETAIL_OPENGL_TEXTURE_HPP_
#define NGY313_DETAIL_OPENGL_TEXTURE_HPP_

#include <cassert>
#include <memory>
#include <tuple>
#include <boost/noncopyable.hpp>
#include <boost/signals2/trackable.hpp>
#include <GL/gl.h>

namespace ngy313 { namespace detail {
template <typename Device>
struct texture_delete {
  explicit texture_delete(const Device &device) : device_(device) {}

  void operator ()(const GLuint *texture) const {
  	assert(texture);
  	const typename Device::scoped_render render(device_);
    glDeleteTextures(1, texture);
    delete texture;
  }
  
 private:
  const Device &device_;
};

typedef std::shared_ptr<GLuint> texture_handle;
typedef std::tuple<texture_handle, int, int> texture_tuple;

template <typename Device>
texture_tuple create_empty_texture(const Device &device,
		                          int width,
		                          int height) {
  const typename Device::scoped_render render(device);
  const texture_handle id(new GLuint(), texture_delete<Device>(device));
  glGenTextures(1, id.get());
  glBindTexture(GL_TEXTURE_2D, *id);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 
                   0,
               GL_RGBA,
               width,
               height, 
                   0,
               GL_RGBA,
               GL_UNSIGNED_BYTE,
               nullptr);
  return texture_tuple(id, width, height);
}

template <typename Device, typename Texture, typename Pred>
texture_tuple create_texture(Device &device, Texture &texture, Pred pred) {
  const typename Device::scoped_render render(device);
  if (render.succeeded()) {
    return pred(device);
  } else {
  	device.after_reset().connect([&device, &texture, pred]() {texture.reset(pred(device));});
  	return texture_tuple(texture_handle(), 0, 0);
  }
}

template <typename Device>
class opengl_texture : public boost::signals2::trackable {
 public:
  typedef const texture_handle &handle_type;
  typedef std::tuple<texture_handle, int, int> texture_tuple;
  typedef texture_delete<Device> deleter_type;

  explicit opengl_texture(Device &device,
  		                     int width,
  		                     int height)
      : data_() {
   data_ = create_texture(device, 
                          *this,
                          [&](Device &device) {
                            return create_empty_texture(device, width, height);
                                 });
  }

  template <typename Image>
  explicit opengl_texture(Device &device,
  		                     const Image &image)
      : data_() {
  	data_ = create_texture(device, *this, image);
  }

  int width() const {
    return std::get<1>(data_);
  }

  int height() const {
    return std::get<2>(data_);
  }

  handle_type handle() const {
    return std::get<0>(data_);
  }

  void reset(texture_tuple &&data) {
    	data_ = data;
    }

 private:
  texture_tuple data_;
};
}}

#endif
