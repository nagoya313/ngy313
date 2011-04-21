#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_FVF_TYPE_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_FVF_TYPE_HPP_
#include <d3d9.h>

namespace ngy313 { namespace graphic { namespace detail {
typedef DWORD fvf_type;

const fvf_type kXYZRHW = D3DFVF_XYZRHW;
const fvf_type kXYZ = D3DFVF_XYZ;
const fvf_type kNormal = D3DFVF_NORMAL;
const fvf_type kDiffuse = D3DFVF_DIFFUSE;
const fvf_type kSpecular = D3DFVF_SPECULAR;
const fvf_type kTex1 = D3DFVF_TEX1;
const fvf_type kTex2 = D3DFVF_TEX2;
}}}

#endif
