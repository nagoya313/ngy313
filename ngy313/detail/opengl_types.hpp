#ifndef NGY313_OPENGL_TYPES_HPP_
#define NGY313_OPENGL_TYPES_HPP_

#include <cstdint>
#include <type_traits>
#include <boost/noncopyable.hpp>
#include <GL/gl.h>

namespace ngy313 { namespace detail {
struct opengl_fvf_type : private boost::noncopyable {
  typedef std::uint32_t value_type;

  static constexpr value_type kXYZ_RHW = 0x00;
  static constexpr value_type kXYZ = 0x00;
  static constexpr value_type kNormal = 0x01;
  static constexpr value_type kDiffuse = 0x02;
  static constexpr value_type kSpecular = 0x04;
  static constexpr value_type kTexture = 0x08;
  static constexpr value_type kMultiTexture = 0x10;
  
  opengl_fvf_type() = delete;
};

struct opengl_primitive_type : private boost::noncopyable {
  typedef GLenum value_type;

  static constexpr value_type kPointList = GL_POINTS;
  static constexpr value_type kLineList = GL_LINES;
  static constexpr value_type kLineStrip = GL_LINE_STRIP;
  static constexpr value_type kTriangleList = GL_TRIANGLES;
  static constexpr value_type kTriangleStrip = GL_TRIANGLE_STRIP;
  static constexpr value_type kTriangleFan = GL_TRIANGLE_FAN;

  opengl_primitive_type() = delete;
};

struct opengl_blend_type : private boost::noncopyable {
  typedef GLenum value_type;

  static constexpr value_type kBlendOne = GL_ONE;
  static constexpr value_type kBlendSrcAlpha = GL_SRC_ALPHA;
  static constexpr value_type kBlendInvSrcAlpha = GL_ONE_MINUS_SRC_ALPHA;
  static constexpr value_type kBlendDestAlpha =  GL_DST_ALPHA;
  static constexpr value_type kBlendInvDestAlpha = GL_ONE_MINUS_DST_ALPHA;
  static constexpr value_type kBlendZero = GL_ZERO;
  static constexpr value_type kBlendSrcColor = GL_SRC_COLOR;
  static constexpr value_type kBlendInvSrcColor = GL_ONE_MINUS_SRC_COLOR;
  static constexpr value_type kBlendDestColor = GL_DST_COLOR;
  static constexpr value_type kBlendInvDestColor = GL_ONE_MINUS_DST_COLOR;

  opengl_blend_type() = delete;
};
}}

#endif
