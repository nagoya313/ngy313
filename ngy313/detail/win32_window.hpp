#ifndef NGY313_DETAIL_WIN32_WINDOW_HPP_
#define NGY313_DETAIL_WIN32_WINDOW_HPP_

#include <cassert>
#include <string>
#include <system_error>
#include <vector>
#include <boost/noncopyable.hpp>
#include <CommCtrl.h>
#include <Windows.h>
#include <ngy313/fwd.hpp>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
class win32_window : boost::noncopyable {
 public:
  typedef HWND handle_type;

  win32_window() : handle_(create_window()) {
    set_subclass_procedure();
    resize(640, 480);
  }

  void show() {
    assert(handle_);
    ShowWindow(handle_, SW_RESTORE);
  }

  void set_caption(const string_wrap &text) {
    assert(handle_);
    SetWindowText(handle_, text.c_str());
  }

  template <typename Icon>
  void set_icon(const basic_icon<Icon> &icon) {
    assert(handle_);
    if (!SetClassLongPtr(handle_,
                         GCLP_HICON,
                         reinterpret_cast<LONG_PTR>(icon.handle()))) {
      throw std::system_error(std::error_code(GetLastError(), 
                                              std::system_category()),
                              "アイコンの設定に失敗しました。\n詳細");
    }
  }

  void move(int x_pos, int y_pos) {
    assert(handle_);
    SetWindowPos(handle_, nullptr, x_pos, y_pos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
    assert(x() == x_pos && y() == y_pos);
  }

  void resize(int width_size, int height_size) {
    assert(handle_);
    RECT rect = {0, 0, width_size, height_size};
    if (!AdjustWindowRect(&rect, kWindowStyle_, FALSE)) {
      throw std::system_error(std::error_code(GetLastError(),
                                              std::system_category()),
                              "ウィンドウサイズの取得に失敗しました。\n詳細");
    }
    SetWindowPos(handle_, 
                 nullptr, 
                 0,
                 0,
                 rect.right - rect.left,
                 rect.bottom - rect.top,
                 SWP_NOMOVE | SWP_NOZORDER);
    assert(width() == width_size && height() == height_size);
  }

  std::string caption() const {
    assert(handle_);
    std::vector<char> buffer(GetWindowTextLength(handle_) + 1);
    GetWindowText(handle_, buffer.data(), buffer.size());
    return std::string(buffer.begin(), buffer.end() - 1);
  }

  int x() const {
    return rect().left;
  }

  int y() const {
    return rect().top;
  }

  int width() const {
    const RECT rect = client_rect();
    return rect.right - rect.left;
  }

  int height() const {
    const RECT rect = client_rect();
    return rect.bottom - rect.top;
  }

  HWND handle() const {
    return handle_;
  }

 private:
  static HWND create_window() {
    const HWND window = CreateWindow("MAINWINDOW", 
                                     "",
                                     kWindowStyle_,
                                     CW_USEDEFAULT,
                                     CW_USEDEFAULT, 
                                     CW_USEDEFAULT,
                                     CW_USEDEFAULT,
                                     nullptr,
                                     nullptr,
                                     GetModuleHandle(nullptr),
                                     nullptr);
    if (!window) {
      throw std::system_error(std::error_code(GetLastError(), 
                                              std::system_category()), 
                              "ウィンドウの作成に失敗しました。\n詳細");
    }
    return window;
  }

  void set_subclass_procedure() {
    assert(handle_);
    if (!SetWindowSubclass(handle_, 
                           &subclass_procedure,
                           reinterpret_cast<UINT_PTR>(this), 
                           0)) {
      throw std::system_error(std::error_code(GetLastError(), 
                                              std::system_category()),
                              "サブクラスプロシージャの設定に失敗しました。\n詳細");
    }
  }


  LRESULT procedure(HWND window_handle, 
                    UINT message, 
                    WPARAM wp,
                    LPARAM lp) {
    switch (message) {
      case WM_DESTROY:
        PostQuitMessage(0);
        break;
      default:
        return DefSubclassProc(window_handle, message, wp, lp);
    }
    return 0;
  }

  static LRESULT CALLBACK subclass_procedure(HWND window_handle,
                                             UINT message,
                                             WPARAM wp,
                                             LPARAM lp,
                                             UINT_PTR self,
                                             DWORD_PTR ref) {

    UNREFERENCED_PARAMETER(ref);
    assert(reinterpret_cast<win32_window *>(self));
    return reinterpret_cast<win32_window *>(self)->procedure(window_handle,
                                                             message,
                                                             wp,
                                                             lp);
  }

  RECT rect() const {
    assert(handle_);
    RECT rc;
    GetWindowRect(handle_, &rc);
    return rc;
  }

  RECT client_rect() const {
    assert(handle_);
    RECT rc;
    GetClientRect(handle_, &rc);
    return rc;
  }

  HWND handle_;
  static const DWORD kWindowStyle_ = 
      WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
};
}}

#endif
