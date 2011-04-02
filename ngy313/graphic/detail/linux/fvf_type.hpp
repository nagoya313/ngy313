#ifndef NGY313_GRAPHIC_DETAIL_LINUX_FVF_TYPE_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_FVF_TYPE_HPP_
#include <cstdint>
#include <GL/gl.h>

namespace ngy313 { namespace graphic { namespace detail {
typedef std::uint32_t fvf_type;

const fvf_type kXYZRHW = 0x0;
const fvf_type kXYZ = 0x0;
const fvf_type kNormal = 0x1;
const fvf_type kDiffuse = 0x02;
const fvf_type kSpecular = 0x04;
const fvf_type kTex1 = 0x08;
const fvf_type kTex2 = 0x10;
}}}

#endif

