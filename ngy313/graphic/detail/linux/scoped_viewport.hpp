#ifndef NGY313_GRAPHIC_DETAIL_LINUX_SCOPED_VIEWPORT_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_SCOPED_VIEWPORT_HPP_
#include <boost/noncopyable.hpp>

namespace ngy313 { namespace graphic { namespace detail {
void set_viewport(const int width, const int height) {
  glViewport(0, 0, width, height);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.f, static_cast<float>(width), static_cast<float>(height), 0.f, 0.f, 1.f);
}

class scoped_viewport : private boost::noncopyable {
 public:
  explicit scoped_viewport(const device_handle &device) : device_(device) {}

  ~scoped_viewport() {
    set_viewport(device_.width(), device_.height());
  }

 private:
  const device_handle &device_;
};
}}}

#endif

