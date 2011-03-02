#pragma once
#include <ngy313/graphic/detail/device.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
surface_handle render_target(const device_handle &device) {
  assert(device);
  LPDIRECT3DSURFACE9 target;
  device->GetRenderTarget(0, &target);
  return surface_handle(target);
}

inline
void set_render_target(const device_handle &device, const surface_handle &surface) {
  assert(device);
  assert(surface);
  device->SetRenderTarget(0, surface.get());
}

}}}
