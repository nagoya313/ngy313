#pragma once
#include <cassert>
#include <ngy313/graphic/detail/blend_type.hpp>
#include <ngy313/graphic/detail/fwd.hpp>
#include <ngy313/utility/com_delete.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
void set_blend_mode(const device_handle &device, const blend_type src, const blend_type dest) {
  assert(device);
  device->SetRenderState(D3DRS_SRCBLEND, src);
  device->SetRenderState(D3DRS_DESTBLEND, dest);
}

template <typename BlendPair>
void set_blend_pair(const device_handle &device) {
  assert(device);
  set_blend_mode(device, BlendPair::src_type::value, BlendPair::dest_type::value);
}
}}}
