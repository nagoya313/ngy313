#pragma once
#include <d3d9.h>

namespace ngy313 { namespace graphic { namespace detail {
typedef D3DTEXTUREADDRESS addressing_type;

const addressing_type kAddressWrap = D3DTADDRESS_WRAP;
const addressing_type kAddressMirror = D3DTADDRESS_MIRROR;
const addressing_type kAddressClamp = D3DTADDRESS_CLAMP;
}}}
