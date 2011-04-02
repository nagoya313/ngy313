#ifndef NGY313_WINDWO_DETAIL_WINDOWS_MAIN_WINDOW_HPP_
#define NGY313_WINDWO_DETAIL_WINDOWS_MAIN_WINDOW_HPP_
#include <cassert>
#include <cstdint>
#include <string>
#include <system_error>
#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/signals2/signal.hpp>
#include <ngy313/utility/call_once.hpp>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/windows/window.hpp>

namespace ngy313 { namespace window { namespace detail {
class main_window : private boost::noncopyable {
 public:
  main_window() : handle_(init_window()) {
    assert(handle_);
    set_subclass_procedure(handle_, reinterpret_cast<UINT_PTR>(this), &subclass_procedure);
  }

  void show() const {
    assert(handle_);
    ShowWindow(handle_, SW_RESTORE);
  }

  void hide() const {
    assert(handle_);
    ShowWindow(handle_, SW_HIDE);
  }

  void set_caption(const utility::string_piece &text) const {
    assert(handle_);
    SetWindowTextA(handle_, text.c_str());
    assert(text.string() == caption());
  }

  void set_icon() {
    assert(handle_);
    //set_icon(handle_);
  }

  void move(const int x_pos, const int y_pos) const {
    assert(handle_);
    SetWindowPos(handle_, nullptr, x_pos, y_pos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    assert(x() == x_pos);
    assert(y() == y_pos);
  }

  void resize(const int width_size, const int height_size) const {
    assert(handle_);
    RECT rect = {0, 0, width_size, height_size};
    if (!AdjustWindowRect(&rect, kWindowStyle, FALSE)) {
      const DWORD error = GetLastError();
      throw std::system_error(std::error_code(error, std::system_category()),
                              "ウィンドウサイズの取得に失敗しました。\n詳細");
    }
    SetWindowPos(handle_, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
    assert(width() == width_size);
    assert(height() == height_size);
  }

  std::string caption() const {
    assert(handle_);
    std::vector<char> buffer(GetWindowTextLength(handle_) + 1);
    GetWindowTextA(handle_, buffer.data(), buffer.size());
    return std::string(buffer.begin(), buffer.end() - 1);
  }

  int x() const {
    assert(handle_);
    return rect(handle_).left;;
  }

  int y() const {
    assert(handle_);
    return rect(handle_).top;;
  }

  int width() const {
    assert(handle_);
    RECT rect = client_rect(handle_);
    return rect.right - rect.left;
  }

  int height() const {
    assert(handle_);
    RECT rect = client_rect(handle_);
    return rect.bottom - rect.top;
  }

  boost::signals2::signal<void (std::uint32_t)> key_down;

  boost::signals2::signal<void (std::uint32_t)> key_up;

  boost::signals2::signal<void (std::uint32_t)> key_triger;

  handle window() const {
    return handle_;
  }

 private:
  static detail::handle init_window() {
    const utility::call_once once([] {regist_window_class("BASE");});
    return create_window("BASE");
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
    UNREFERENCED_PARAMETER(ref);
    assert(reinterpret_cast<main_window *>(self));
    return reinterpret_cast<main_window *>(self)->procedure(window_handle, message, wp, lp);
  }

  const handle handle_;
};
}}}

#endif
