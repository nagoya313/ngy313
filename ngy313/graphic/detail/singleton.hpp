#pragma once
#include <boost/signals2/signal.hpp>
#include <ngy313/graphic/detail/device.hpp>
#include <ngy313/graphic/detail/graphic_device.hpp>
#include <ngy313/window/detail/singleton.hpp>

namespace ngy313 { namespace graphic { namespace detail {
class singleton : private boost::noncopyable {
 public:
  static singleton &instance() {
    static singleton graphic;
    return graphic;
  }

  graphic_device &device() {
    return device_;
  }

 private:
  singleton() : device_(window::detail::window()) {
    init_device(device_.device());
  }
  
  graphic_device device_;
};

inline
graphic_device &device() {
  return singleton::instance().device();
}
}}}
