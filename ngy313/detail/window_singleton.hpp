#pragma once
#include <boost/mpl/string.hpp>
#include <boost/signals2/signal.hpp>
#include "singleton.hpp"
#include "window.hpp"
#include "graphic_device.hpp"

namespace ngy313 { namespace detail {
class window_singleton : public singleton<window_singleton> {
 public:
  const window_handle &window() const {
    return window_;
  }

  const graphic_device_handle &graphic_device() const {
    return graphic_device_;
  }

  boost::signals2::signal<void ()> before_reset;

  boost::signals2::signal<void ()> after_reset;

  boost::signals2::signal<void ()> input_callback;

 private:
  typedef boost::mpl::string<'BASE'> window_class_name;

  window_singleton() : window_(init_window()),
                       graphic_base_(create_graphic_base()),
                       graphic_device_(create_graphic_device(window_, graphic_base_, true)) {
    set_procedure(window_, &procedure);
    init_device(graphic_device_);
  }

  static window_handle init_window() {
    regist_window_class<window_class_name>();
    return create_window<window_class_name>();
  }

  static LRESULT CALLBACK procedure(const HWND window_handle, const UINT message, const WPARAM wp, const LPARAM lp) {
    switch (message) {
      case WM_CLOSE:
        PostQuitMessage(0);
        break;
      default:
        return DefWindowProc(window_handle, message, wp, lp);
    }
    return 0;
  }

  const window_handle window_;
  const graphic_base_handle graphic_base_;
  const graphic_device_handle graphic_device_;

  friend singleton<window_singleton>;
};

const window_handle &window() {
  return window_singleton::instance().window();
}

const graphic_device_handle &graphic_device() {
  return window_singleton::instance().graphic_device();
}

boost::signals2::signal<void ()> &before_reset() {
  return window_singleton::instance().before_reset;
}

boost::signals2::signal<void ()> &after_reset() {
  return window_singleton::instance().after_reset;
}

boost::signals2::signal<void ()> &input_callback() {
  return window_singleton::instance().input_callback;
}
}}
