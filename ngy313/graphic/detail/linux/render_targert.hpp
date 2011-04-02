#pragma once
#include <stdexcept>
#include <ngy313/graphic/detail/device.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
surface_handle render_target(const device_handle &device) {
  assert(device);
  LPDIRECT3DSURFACE9 target;
  if (FAILED(device->GetRenderTarget(0, &target))) {
    throw std::runtime_error("レンダリングターゲットのサーフエイスの取得に失敗しました");
  }
  return surface_handle(target);
}

inline
void set_render_target(const device_handle &device, const surface_handle &surface) {
  assert(device);
  assert(surface);
  device->SetRenderTarget(0, surface.get());
}

}}}
