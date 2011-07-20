#ifndef NGY313_WINDWO_DETAIL_WINDOWS_MAIN_WINDOW_HPP_
#define NGY313_WINDWO_DETAIL_WINDOWS_MAIN_WINDOW_HPP_
#include <cassert>
#include <cstdint>
#include <string>
#include <system_error>
#include <vector>
#include <boost/noncopyable.hpp>
#pragma warning(disable: 4512)
#include <boost/signals2/signal.hpp>
#pragma warning(default: 4512)
#include <ngy313/utility/call_once.hpp>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/windows/window.hpp>

namespace ngy313 { namespace window { namespace detail {
class main_window : private boost::noncopyable {
 public:
  main_window() : handle_(init_window()), icon_("default_icon") {
    assert(handle_);
    set_subclass_procedure(handle_, reinterpret_cast<UINT_PTR>(this), &subclass_procedure);
  }

  void show() {
    assert(handle_);
    ShowWindow(handle_, SW_RESTORE);
  }

  void set_caption(const utility::string_piece &text) {
    assert(handle_);
    SetWindowTextA(handle_, text.c_str());
    assert(text.string() == caption());
  }

  void set_icon(const utility::string_piece &icon_name) {
    assert(handle_);
    const HICON handle = reinterpret_cast<HICON>(LoadImageA(nullptr, 
                                                 icon_name.c_str(),
                                                 IMAGE_ICON, 
                                                 32,
                                                 32,
                                                 LR_DEFAULTSIZE | LR_SHARED | LR_LOADFROMFILE));
    if (!handle) {
      const DWORD error = GetLastError();
      throw std::system_error(std::error_code(error, std::system_category()),
                              "�A�C�R���̓ǂݍ��݂Ɏ��s���܂����B\n�ڍ�");
    }
    if (!SetClassLongPtr(handle_, GCLP_HICON, reinterpret_cast<LONG_PTR>(handle))) {
      const DWORD error = GetLastError();
      throw std::system_error(std::error_code(error, std::system_category()),
                              "�A�C�R���̐ݒ�Ɏ��s���܂����B\n�ڍ�");
    }
    icon_ = icon_name.string();
    assert(icon() == icon_name.string());
  }

  std::string icon() const {
    return icon_;
  }

  void move(const int x_pos, const int y_pos) {
    assert(handle_);
    SetWindowPos(handle_, nullptr, x_pos, y_pos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    assert(x() == x_pos);
    assert(y() == y_pos);
  }

  void resize(const int width_size, const int height_size) {
    assert(handle_);
    RECT rect = {0, 0, width_size, height_size};
    if (!AdjustWindowRect(&rect, kWindowStyle, FALSE)) {
      const DWORD error = GetLastError();
      throw std::system_error(std::error_code(error, std::system_category()),
                              "�E�B���h�E�T�C�Y�̎擾�Ɏ��s���܂����B\n�ڍ�");
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
    //UNREFERENCED_PARAMETER(ref);
    assert(reinterpret_cast<main_window *>(self));
    return reinterpret_cast<main_window *>(self)->procedure(window_handle, message, wp, lp);
  }

  const handle handle_;
  std::string icon_;
};
}}}

#endif