#pragma once
#include <boost/noncopyable.hpp>
#include <ngy313/sound/detail/com_initializer.hpp>
#include <ngy313/sound/detail/device.hpp>

namespace ngy313 { namespace sound { namespace detail {
class singleton : private boost::noncopyable {
 public:
  static const singleton &instance() {
    static const singleton sound;
    return sound;
  }

  const device_handle &device() const {
    return device_;
  }

  const master_voice_handle &master_voice() const {
    return voice_;
  }

 private:
  singleton() : com_(), device_(create_device()), voice_(create_master_voice(device_)) {}

  const com_initializer com_;
  const device_handle device_;
  const master_voice_handle voice_;
};

inline
const device_handle &device() {
  return singleton::instance().device();
}

inline
const master_voice_handle &master_voice() {
  return singleton::instance().master_voice();
}
}}}
