#ifndef NGY313_PROCESS_DETAIL_PROCESS_HPP_
#define NGY313_PROCESS_DETAIL_PROCESS_HPP_
#include <ngy313/platform.hpp>
#include <ngy313/process/detail/singleton.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/process/detail/windows/process.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/process/detail/linux/process.hpp>
#endif

namespace ngy313 { namespace process { namespace detail {
inline 
main_process &process() {
  return singleton<main_process>::instance().process();
}
}}}

#endif

