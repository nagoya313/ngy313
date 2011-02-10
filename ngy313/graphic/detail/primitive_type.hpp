#pragma once
#include <d3d9.h>

namespace ngy313 { namespace graphic { namespace detail {
typedef D3DPRIMITIVETYPE primitive_type;

const primitive_type kPointList = D3DPT_POINTLIST;
const primitive_type kLineList = D3DPT_LINELIST;
const primitive_type kLineStrip = D3DPT_LINESTRIP;
const primitive_type kTriangleList = D3DPT_TRIANGLELIST;
const primitive_type kTriangleStrip = D3DPT_TRIANGLESTRIP;
const primitive_type KTriangleFan = D3DPT_TRIANGLEFAN;
}}}
