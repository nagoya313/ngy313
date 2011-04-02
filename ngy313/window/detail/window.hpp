#ifndef NGY313_WINDOW_DETAIL_WINDOW_HPP_
#define NGY313_WINDOW_DETAIL_WINDOW_HPP_
#include <ngy313/platform.hpp>
#include <ngy313/window/detail/singleton.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/window/detail/windows/main_window.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/window/detail/linux/main_window.hpp>
#endif

namespace ngy313 { namespace window { namespace detail {
inline
main_window &window() {
  return singleton<main_window>::instance().window();
}
}}}

#endif
