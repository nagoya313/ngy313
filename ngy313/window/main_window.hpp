#pragma once
#include <cassert>
#include <string>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace window {
// ひょっとするとインスタンスベースのライブラリに戻す可能性を含ませたクラス
class main_window {
 public:
  main_window() : handle_(init_window()) {
    assert(handle_);
    detail::set_procedure(handle_, &procedure);
  }

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

 private:
  typedef boost::mpl::string<'TEST'> window_class_name;

  static detail::handle init_window() {
    // 一回だけ呼ぶように仕掛ける必要がある
    detail::regist_window_class<window_class_name>();
    return detail::create_window<window_class_name>();
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

  const detail::handle handle_;
};
}}
