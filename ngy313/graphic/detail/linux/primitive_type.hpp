#ifndef NGY313_GRAPHIC_DETAIL_LINUX_PRIMITIVE_TYPE_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_PRIMITIVE_TYPE_HPP_
#include <GL/gl.h>

namespace ngy313 { namespace graphic { namespace detail {
typedef GLenum primitive_type;

const primitive_type kPointList = GL_POINTS;
const primitive_type kLineList = GL_LINES;
const primitive_type kLineStrip = GL_LINE_STRIP;
const primitive_type kTriangleList = GL_TRIANGLES;
const primitive_type kTriangleStrip = GL_TRIANGLE_STRIP;
const primitive_type KTriangleFan = GL_TRIANGLE_FAN;
}}}

#endif

