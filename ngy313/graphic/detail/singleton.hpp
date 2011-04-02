#ifndef NGY313_GRAPHIC_DETAIL_SINGLETON_HPP_
#define NGY313_GRAPHIC_DETAIL_SINGLETON_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace graphic { namespace detail {
template <typename Device>
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
  }
  
  Device device_;
};
}}}

#endif
