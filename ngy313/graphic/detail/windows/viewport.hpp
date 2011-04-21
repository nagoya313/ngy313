#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_VIEWPORT_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_VIEWPORT_HPP_
#include <ngy313/graphic/detail/windows/device.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
viewport init_viewport(const int width, const int height) {
  const viewport view = {0, 0, width, height, 0.f, 1.f};
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

#endif
