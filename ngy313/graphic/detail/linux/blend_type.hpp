#ifndef NGY313_GRAPHIC_DETAIL_LINUX_BLEND_TYPE_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_BLEND_TYPE_HPP_
#include <GL/gl.h>

namespace ngy313 { namespace graphic { namespace detail {
typedef GLenum blend_type;

const blend_type kBlendOne = GL_ONE;
const blend_type kBlendSrcAlpha = GL_SRC_ALPHA;
const blend_type kBlendInvSrcAlpha = GL_ONE_MINUS_SRC_ALPHA;
// const blend_type kBlendDestAlpha = GL_DEST_ALPHA;
// const blend_type kBlendInvDestAlpha = GL_ONE_MINUS_DEST_ALPHA;
const blend_type kBlendZero = GL_ZERO;
const blend_type kBlendSrcColor = GL_SRC_COLOR;
const blend_type kBlendInvSrcColor = GL_ONE_MINUS_SRC_COLOR;
const blend_type kBlendDestColor = GL_DST_COLOR;
const blend_type kBlendInvDestColor = GL_ONE_MINUS_DST_COLOR;
}}}

#endif

