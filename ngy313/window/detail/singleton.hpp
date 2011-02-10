#pragma once
#include <boost/mpl/string.hpp>
#include <boost/noncopyable.hpp>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace window { namespace detail {
class singleton : private boost::noncopyable {
 public:
  static const singleton &instance() {
    static const singleton window;
    return window;
  }

  const handle &window() const {
    return window_;
  }

 private:
  typedef boost::mpl::string<'BASE'> window_class_name;

  singleton() : window_(init_window()) {
    set_procedure(window_, &procedure);
    resize(window_, 640, 480);
  }

  static handle init_window() {
    regist_window_class<window_class_name>();
    return create_window<window_class_name>();
  }

  static LRESULT CALLBACK procedure(const HWND window_handle, const UINT message, const WPARAM wp, const LPARAM lp) {
    switch (message) {
      case WM_DESTROY:
        PostQuitMessage(0);
        break;
      default:
        return DefWindowProc(window_handle, message, wp, lp);
    }
    return 0;
  }

  const handle window_;
};

inline
const handle &window() {
  return singleton::instance().window();
}
}}}
