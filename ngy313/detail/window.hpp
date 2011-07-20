#ifndef NGY313_DETAIL_WINDOW_HPP_
#define NGY313_DETAIL_WINDOW_HPP_

#include <cassert>
#include <ngy313/fwd.hpp>
#include <ngy313/string_wrap.hpp>

#if defined(_WIN32)
#include <ngy313/detail/win32_window.hpp>
#elif defined(__linux__)
#include <ngy313/detail/gtkmm_window.hpp>
#endif

namespace ngy313 { namespace detail {
template <typename Window>
class basic_window {
 public:
  basic_window() : window_() {}

  void show() {
    window_.show();
  }

  void set_caption(const string_wrap &text) {
    window_.set_caption(text);
    assert(text == caption());
  }

  template <typename Icon>
  void set_icon(const basic_icon<Icon> &icon) {
    window_.set_icon(icon);
  }

  void move(int x_pos, int y_pos) {
    window_.move(x_pos, y_pos);
    assert(x() == x_pos && y() == y_pos);
  }

  void resize(int width_size, int height_size) {
    window_.resize(width_size, height_size);
    assert(width() == width_size && height() == height_size);
  }

  std::string caption() const {
    return window_.caption();
  }

  int x() const {
    return window_.x();
  }

  int y() const {
    return window_.y();
  }

  int width() const {
    return window_.width();
  }

  int height() const {
    return window_.height();
  }

  typename Window::handle_type handle() const {
    return window_.handle();
  }

 private:
  basic_window(const basic_window &rhs);
  basic_window &operator =(const basic_window &rhs);

  Window window_;
};

#if defined(_WIN32)
typedef basic_window<win32_window> window; 
#elif defined(__linux__)
typedef basic_window<gtkmm_window> window;
#endif
}}

#endif
