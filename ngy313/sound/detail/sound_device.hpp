#pragma once
#include <boost/noncopyable.hpp>
#include <ngy313/sound/detail/device.hpp>
#include <ngy313/utility/com_initializer.hpp>

namespace ngy313 { namespace sound { namespace detail {
class sound_device : private boost::noncopyable {
 public:
  sound_device() : com_(), device_(create_device()), voice_(create_master_voice(device_)) {}

  const device_handle &device() const {
    return device_;
  }

  const master_voice_handle &master_voice() const {
    return voice_;
  }

 private:
  const utility::com_initializer com_;
  const device_handle device_;
  const master_voice_handle voice_;
};
}}}
