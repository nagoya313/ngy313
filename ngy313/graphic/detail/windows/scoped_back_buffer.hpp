#ifndef NGY313_GRAPHIC_DETAIL_WINDOWS_SCOPED_BACK_BUFFER_HPP_
#define NGY313_GRAPHIC_DETAIL_WINDOWS_SCOPED_BACK_BUFFER_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/graphic/detail/windows/device.hpp>

namespace ngy313 { namespace graphic { namespace detail {
class scoped_back_buffer : private boost::noncopyable {
 public:
  explicit scoped_back_buffer(const device_handle &device) : device_(device), back_buffer_(render_surface(device_)) {}

  ~scoped_back_buffer() {
    set_render_surface(device_, back_buffer_);
  }

 private:
  const device_handle &device_;
  const surface_handle back_buffer_;
};
}}}

#endif
