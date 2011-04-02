#ifndef NGY313_GRAPHIC_DETAIL_GRAPHIC_HPP_
#define NGY313_GRAPHIC_DETAIL_GRAPHIC_HPP_
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/draw.hpp>
#include <ngy313/graphic/detail/windows/graphic_device.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/draw.hpp>
#include <ngy313/graphic/detail/linux/graphic_device.hpp>
#endif
#include <ngy313/graphic/detail/singleton.hpp>

namespace ngy313 { namespace graphic { namespace detail {
inline
graphic_device &device() {
  return singleton<graphic_device>::instance().device();
}
}}}

#endif
