#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_BLEND_TYPE_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_BLEND_TYPE_HPP_
#include <d3d9.h>

namespace ngy313 { namespace graphic { namespace detail {
typedef D3DBLEND blend_type;

const blend_type kBlendOne = D3DBLEND_ONE;
const blend_type kBlendSrcAlpha = D3DBLEND_SRCALPHA;
const blend_type kBlendInvSrcAlpha = D3DBLEND_INVSRCALPHA;
const blend_type kBlendZero = D3DBLEND_ZERO;
const blend_type kBlendSrcColor = D3DBLEND_SRCCOLOR;
const blend_type kBlendInvSrcColor = D3DBLEND_INVSRCCOLOR;
const blend_type kBlendDestColor = D3DBLEND_DESTCOLOR;
const blend_type kBlendInvDestColor = D3DBLEND_INVDESTCOLOR;
}}}

#endif
