#ifndef NGY313_GRAPHIC_DETAIL_LINUX_ADDRESSING_TYPE_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_ADDRESSING_TYPE_HPP_
#include <GL/gl.h>

namespace ngy313 { namespace graphic { namespace detail {
typedef GLenum addressing_type;

const addressing_type kAddressWrap = GL_REPEAT;
//const addressing_type kAddressMirror = GL_MIRROR;
const addressing_type kAddressClamp = GL_CLAMP;
}}}

#endif

