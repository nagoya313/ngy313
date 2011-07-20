#ifndef NGY313_OPENGL_TYPES_HPP_
#define NGY313_OPENGL_TYPES_HPP_

#include <cstdint>
#include <type_traits>
#include <boost/noncopyable.hpp>
#include <GL/gl.h>

namespace ngy313 { namespace detail {
struct opengl_fvf_type : private boost::noncopyable {
  typedef std::uint32_t value_type;

  typedef boost::mpl::integral_c<value_type, 0x00> xyz_rhw;
  typedef boost::mpl::integral_c<value_type, 0x00> xyz;
  typedef boost::mpl::integral_c<value_type, 0x01> normal;
  typedef boost::mpl::integral_c<value_type, 0x02> diffuse;
  typedef boost::mpl::integral_c<value_type, 0x04> specular;
  typedef boost::mpl::integral_c<value_type, 0x08> texture;
  typedef boost::mpl::integral_c<value_type, 0x10> multi_texture;
  
  opengl_fvf_type() = delete;
};

struct opengl_primitive_type : private boost::noncopyable {
  typedef GLenum value_type;

  typedef std::integral_constant<value_type, GL_POINTS> point_list;
  typedef std::integral_constant<value_type, GL_LINES> line_list;
  typedef std::integral_constant<value_type, GL_LINE_STRIP> line_strip;
  typedef std::integral_constant<value_type, GL_TRIANGLES> triangle_list;
  typedef std::integral_constant<value_type, GL_TRIANGLE_STRIP> triangle_strip;
  typedef std::integral_constant<value_type, GL_TRIANGLE_FAN> triangle_fan;
  
  opengl_primitive_type() = delete;
};
}}

#endif