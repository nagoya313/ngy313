#ifndef NGY313_DETAIL_OPENGL_TEXTURE_HPP_
#define NGY313_DETAIL_OPENGL_TEXTURE_HPP_

#include <cassert>
#include <functional>
#include <memory>
#include <tuple>
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>
#include <boost/signals2/trackable.hpp>
#include <GL/gl.h>

namespace ngy313 { namespace detail {
template <typename Device>
struct texture_delete {
  explicit texture_delete(const Device &device) : device_(&device) {}

  void operator ()(const GLuint *texture) const {
  	assert(texture && device_);
  	const typename Device::scoped_render render(*device_);
    glDeleteTextures(1, texture);
    delete texture;
  }
  
 private:
  const Device *device_;
};

template <typename Device>
struct texture_handle {
  typedef std::unique_ptr<GLuint, texture_delete<Device>> type;
};

template <typename Device>
struct texture_tuple {
  typedef std::tuple<typename texture_handle<Device>::type, int, int> type;
};

template <typename Device,
          typename Result = typename texture_tuple<Device>::type>
Result create_empty_texture(const Device &device, int width, int height) {
  const typename Device::scoped_render render(device);
  typename texture_handle<Device>::type id(new GLuint(), 
                                           texture_delete<Device>(device));
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
  return std::make_tuple(std::move(id), width, height);
}

template <typename Device, 
          typename Texture,
          typename Pred,
          typename Result = typename texture_tuple<Device>::type>
Result create_texture(Device &device, Texture &texture, Pred pred) {
  const typename Device::scoped_render render(device);
  if (render.succeeded()) {
    return pred(device);
  } else {
	const auto func = [&device, pred] {return pred(device);};
  	device.after_reset().connect(boost::bind(
  	                                 &Texture::template reset<decltype(func)>,
                                 &texture,
                                 func));
  	return std::make_tuple(typename texture_handle<Device>::type(
  	                           nullptr, 
  	                           texture_delete<Device>(device)),
  	                       0,
  	                       0);
  }
}

template <typename Device>
class opengl_texture : public boost::signals2::trackable {
 public:
  typedef const typename texture_handle<Device>::type &handle_type;
  typedef std::tuple<typename texture_handle<Device>::type, 
                     int,
                     int> texture_tuple;

  explicit opengl_texture(Device &device, int width, int height)
      : data_(create_texture(device, 
                             *this,
                             [&](Device &device) {
                               return create_empty_texture(device, 
                                                           width,
                                                           height);
                             })) {}

  template <typename Image>
  explicit opengl_texture(Device &device, const Image &image)
      : data_(create_texture(device, *this, image)) {}

  int width() const {
    return std::get<1>(data_);
  }

  int height() const {
    return std::get<2>(data_);
  }

  handle_type handle() const {
    return std::get<0>(data_);
  }

  template <typename Pred>
  void reset(Pred data) {
    data_ = data();
  }

 private:
  texture_tuple data_;
};
}}

#endif
