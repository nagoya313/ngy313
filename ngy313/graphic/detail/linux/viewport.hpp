#pragma once
#include <cstdint>
#include <ngy313/graphic/detail/device.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
viewport init_viewport(const float width, const float height) {
  const viewport view = {0, 0, static_cast<std::uint32_t>(width), static_cast<std::uint32_t>(height), 0.f, 1.f};
  return view;
}

inline
viewport current_viewport(const device_handle &device) {
  assert(device);
  viewport view;
  device->GetViewport(&view);
  return view;
}

inline
void set_viewport(const device_handle &device, const viewport &view) {
  assert(device);
  device->SetViewport(&view);
}
}}}
