#ifndef NGY313_GRAPHIC_DETAIL_LINUX_IMAGE_LOADER_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_IMAGE_LOADER_HPP_
#include <cassert>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
#include <boost/functional/hash.hpp>
#include <boost/noncopyable.hpp>
#include <GL/gl.h>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/texture_access.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/graphic/detail/linux/graphic_device.hpp>
#include <ngy313/graphic/detail/graphic.hpp>
#include <ngy313/graphic/detail/linux/texture.hpp>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace graphic { namespace detail {
struct texture_key {
  texture_key(graphic_device &dev, const std::string &nam) : device(dev), name(nam) {}

  graphic_device &device;
  std::string name;

 private:
  texture_key &operator =(const texture_key &);
};

inline
bool operator ==(const texture_key &lhs, const texture_key &rhs) {
  return &lhs.device == &rhs.device && lhs.name == rhs.name;
}

inline
std::size_t hash_value(const texture_key &key) {
  std::size_t hash = 0;
  boost::hash_combine(hash, &key.device);
  boost::hash_combine(hash, key.name);
  return hash;
}

inline
std::tuple<texture_handle, int, int> create_texture_from_file(const texture_key &key) {
  // 実装が不完全
  const boost::gil::point2<std::ptrdiff_t> dim = boost::gil::png_read_dimensions(key.name);
  boost::gil::rgb8_image_t src;
  boost::gil::png_read_image(key.name, src);
  GLuint handle;
  key.device.begin_scene();
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, dim.x, dim.y, GL_RGB, GL_UNSIGNED_BYTE, boost::gil::interleaved_view_get_raw_data(boost::gil::view(src)));
  key.device.end_scene();
  return std::tuple<texture_handle, int, int>(texture_handle(handle, key.device), dim.x, dim.y);
}

// そのうち使う
/*
struct default_texture_reader {
 public:
  std::tuple<texture_handle, float, float> operator ()(const texture_key &key) const {
    return std::tuple<texture_handle, float, float>(texture_handle(0), 0.f, 0.f);
  }
};*/

class texture_data : private boost::noncopyable {
 public:
  explicit texture_data(const texture_key &key) : data_(create_texture_from_file(key)) {}

  const texture_handle &texture() const {
    return std::get<0>(data_);
  }

  int width() const {
    return std::get<1>(data_);
  }

  int height() const {
    return std::get<2>(data_);
  }

 private:
  const std::tuple<texture_handle, int, int> data_;
};

inline
texture_key init_texture_key(const utility::string_piece &file_name) {
  return texture_key(device(), file_name.string());
}

typedef boost::flyweights::flyweight<boost::flyweights::key_value<texture_key, texture_data>> texture_type;
}}}

#endif
