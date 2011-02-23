#pragma once
#include <boost/mpl/string.hpp>
#include <boost/noncopyable.hpp>
#include <ngy313/window/detail/main_window.hpp>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace window { namespace detail {
class singleton : private boost::noncopyable {
 public:
  static singleton &instance() {
    static singleton window;
    return window;
  }

  main_window &window() {
    return window_;
  }

 private:
  singleton() : window_() {
    window_.resize(640, 480);
  }

  main_window window_;
};

inline
main_window &window() {
  return singleton::instance().window();
}
}}}
