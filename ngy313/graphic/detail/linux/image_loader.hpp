#ifndef NGY313_GRAPHIC_DETAIL_LINUX_IMAGE_LOADER_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_IMAGE_LOADER_HPP_
#include <cassert>
#include <stdexcept>
#include <string>
#include <tuple>
#include <vector>
#include <boost/gil/gil_all.hpp>
#include <boost/gil/extension/io/png_io.hpp>
#include <boost/gil/extension/io/jpeg_io.hpp>
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
inline
std::tuple<texture_handle, int, int> 
    create_texture_from_alpha_png_file(const device_handle &device, const utility::string_piece &file_name) {
  const boost::gil::point2<std::ptrdiff_t> dim = boost::gil::png_read_dimensions(key.name);
  boost::gil::rgba8_image_t src;
  boost::gil::png_read_image(file_name, src);
  GLuint handle;
  device.begin_scene();
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, dim.x, dim.y, GL_RGBA, GL_UNSIGNED_BYTE, boost::gil::interleaved_view_get_raw_data(boost::gil::view(src)));
  device.end_scene();
  return std::tuple<texture_handle, int, int>(texture_handle(&handle, texture_delete(device)), dim.x, dim.y);

inline
std::tuple<texture_handle, int, int>
    create_texture_from_non_alpha_png_file(const device_handle &device, const utility::string_piece &file_name) {
  const boost::gil::point2<std::ptrdiff_t> dim = boost::gil::png_read_dimensions(key.name);
  boost::gil::rgb8_image_t src;
  boost::gil::png_read_image(file_name, src);
  GLuint handle;
  device.begin_scene();
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, dim.x, dim.y, GL_RGB, GL_UNSIGNED_BYTE, boost::gil::interleaved_view_get_raw_data(boost::gil::view(src)));
  device.end_scene();
  return std::tuple<texture_handle, int, int>(texture_handle(&handle, texture_delete(device)), dim.x, dim.y);
}

inline
std::tuple<texture_handle, int, int> 
    create_texture_from_jpeg_file(const device_handle &device, const utility::string_piece &file_name) {
  const boost::gil::point2<std::ptrdiff_t> dim = boost::gil::png_read_dimensions(key.name);
  boost::gil::rgb8_image_t src;
  boost::gil::jpeg_read_image(file_name, src);
  GLuint handle;
  device.begin_scene();
  glEnable(GL_TEXTURE_2D);
  glGenTextures(1, &handle);
  glBindTexture(GL_TEXTURE_2D, handle);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 3, dim.x, dim.y, GL_RGB, GL_UNSIGNED_BYTE, boost::gil::interleaved_view_get_raw_data(boost::gil::view(src)));
  device.end_scene();
  return std::tuple<texture_handle, int, int>(texture_handle(&handle, texture_delete(device)), dim.x, dim.y);
}
}}}

#endif
