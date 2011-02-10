#pragma once
#include <boost/signals2/signal.hpp>
#include <ngy313/graphic/detail/device.hpp>
#include <ngy313/window/detail/singleton.hpp>

namespace ngy313 { namespace graphic { namespace detail {
class singleton : private boost::noncopyable {
 public:
  static singleton &instance() {
    static singleton graphic;
    return graphic;
  }

  bool windowed() const {
    return windowed_;
  }

  const device_handle &device() const {
    return device_;
  }

  before_reset_signal before_reset;
  after_reset_signal after_reset;

 private:
  singleton() : windowed_(true),
                base_(create_base()),
                device_(create_device(window::detail::window(), base_, windowed_)) {
    init_device(device_);
  }

  bool windowed_;
  const base_handle base_;
  const device_handle device_;
};

inline
const device_handle &device() {
  return singleton::instance().device();
}

inline
bool windowed() {
  return singleton::instance().windowed();
}

inline
before_reset_signal &before_reset() {
  return singleton::instance().before_reset;
}

inline
after_reset_signal &after_reset() {
  return singleton::instance().after_reset;
}
}}}
