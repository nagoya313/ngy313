#pragma once
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/viewport.hpp>

namespace ngy313 { namespace graphic { namespace detail {
class scoped_viewport : private boost::noncopyable {
 public:
  explicit scoped_viewport(const device_handle &device) : device_(device), viewport_(current_viewport(device_)) {}

  ~scoped_viewport() {
    set_viewport(device_, viewport_);
  }

 private:
  const device_handle &device_;
  const viewport viewport_;
};
}}}
