#pragma once
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/device.hpp>

namespace ngy313 { namespace graphic { namespace detail {
class scoped_back_z_and_stencil : private boost::noncopyable {
 public:
  explicit scoped_back_z_and_stencil(const device_handle &device) : device_(device),
                                                                    back_z_and_stencil_(z_and_stencil(device_)) {}

  ~scoped_back_z_and_stencil() {
    set_z_and_stencil(device_, back_z_and_stencil_);
  }

 private:
  const device_handle &device_;
  const surface_handle back_z_and_stencil_;
};
}}}
