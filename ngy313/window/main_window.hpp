#pragma once
#include <cassert>
#include <cstdint>
#include <string>
#include <boost/noncopyable.hpp>
#include <ngy313/utility/call_once.hpp>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace window {
class main_window : private boost::noncopyable {
 public:
  main_window() : handle_(init_window()) {
    assert(handle_);
    detail::set_subclass_procedure(handle_, reinterpret_cast<UINT_PTR>(this), &subclass_procedure);
    detail::resize(640, 480);
  }

  virtual ~main_window() {}

  void show() {
    assert(handle_);
    detail::show(handle_);
  }

  void hide() {
    assert(handle_);
    detail::hide(handle_);
  }

  void set_caption(const utility::string_piece &caption) {
    assert(handle_);
    detail::set_caption(handle_, caption);
    assert(caption.string() == caption());
  }

  void set_icon() {
    assert(handle_);
    detail::set_icon(handle_);
  }

  void move(const int x, const int y) {
    assert(handle_);
    detail::move(handle_, x, y);
  }

  void resize(const int width, const int height) {
    assert(handle_);
    detail::resize(handle_, width, height);
    assert(width() == width);
    assert(height() == height);
  }

  std::string caption() const {
    assert(handle_);
    return detail::caption(handle_);
  }

  int x() const {
    assert(handle_);
    return detail::x(handle_);
  }

  int y() const {
    assert(handle_);
    return detail::y(handle_);
  }

  int width() const {
    assert(handle_);
    return detail::width(handle_);
  }

  int height() const {
    assert(handle_);
    return detail::height(handle_);
  }
  
  virtual key_down(const std::uint32_t code) {}

  virtual key_up(const std::uint32_t code) {}

  virtual key_triger(const std::uint32_t code) {}

 private:
  static detail::handle init_window() {
    const utility::call_once once([] {detail::regist_window_class("TEST");});
    return detail::create_window("TEST");
  }

  LRESULT procedure(const HWND window_handle, const UINT message, const WPARAM wp, const LPARAM lp) {
    switch (message) {
      case WM_KEYDOWN:
        key_down(wp);
        if (!(lp & (1 << 30))) {
          key_triger(wp);
        }
        break;
      case WM_KEYUP:
        key_up(wp);
        break;
      case WM_DESTROY:
        PostQuitMessage(0);
        break;
      default:
        return DefSubclassProc(window_handle, message, wp, lp);
    }
    return 0;
  }

  static LRESULT CALLBACK subclass_procedure(const HWND window_handle,
                                             const UINT message,
                                             const WPARAM wp,
                                             const LPARAM lp,
                                             const UINT_PTR self,
                                             const DWORD_PTR ref) {
    assert(reinterpret_cast<main_window *>(self));
    return reinterpret_cast<main_window *>(self)->procedure(window_handle, message, wp, lp);
  }

  const detail::handle handle_;
};
}}
