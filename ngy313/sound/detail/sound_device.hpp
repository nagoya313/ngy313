#ifndef NGY313_SOUND_DETAIL_SOUND_DEVICE_HPP_
#define NGY313_SOUND_DETAIL_SOUND_DEVICE_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/sound/detail/windows/sound_device.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/sound/detail/linux/sound_device.hpp>
#endif
#include <ngy313/sound/detail/singleton.hpp>

namespace ngy313 { namespace sound { namespace detail {
inline
const sound_device &device() {
  return singleton<sound_device>::instance().device();
}
}}}

#endif
