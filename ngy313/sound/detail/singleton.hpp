#pragma once
#include <boost/noncopyable.hpp>
#include <ngy313/sound/detail/sound_device.hpp>
#include <ngy313/sound/detail/device.hpp>
#include <ngy313/utility/com_initializer.hpp>

namespace ngy313 { namespace sound { namespace detail {
class singleton : private boost::noncopyable {
 public:
  static const singleton &instance() {
    static const singleton sound;
    return sound;
  }

  const sound_device &device() const {
    return device_;
  }

 private:
  singleton() : device_() {}

  const sound_device device_;
};

inline
const sound_device &device() {
  return singleton::instance().device();
}
}}}
