#pragma once
#include <cassert>
#include <memory>
#include <string>
#include <vector>
#include <boost/mpl/string.hpp>
#include <Windows.h>
#include "string_piece.hpp"
#include "last_error.hpp"

namespace ngy313 { namespace detail {
const std::uint32_t kWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

struct window_delete {
  void operator ()(const HWND window) const {
    assert(window);
    DestroyWindow(window);
  }
};

typedef std::unique_ptr<std::remove_pointer<HWND>::type, window_delete>  window_handle;

template <typename MPLString>
void regist_window_class() {
  const WNDCLASSEX window_class  = {
    sizeof(window_class),
    CS_HREDRAW | CS_VREDRAW,
    &DefWindowProc,
    0,
    0,
    GetModuleHandle(nullptr),
    reinterpret_cast<HICON>(LoadImage(nullptr, 
                                      MAKEINTRESOURCE(IDI_APPLICATION), 
                                      IMAGE_ICON, 
                                      32,
                                      32,
                                      LR_DEFAULTSIZE | LR_SHARED)),
    reinterpret_cast<HCURSOR>(LoadImage(nullptr,
                                        MAKEINTRESOURCE(IDC_ARROW), 
                                        IMAGE_CURSOR, 
                                        0,
                                        0,
                                        LR_DEFAULTSIZE | LR_SHARED)),
    reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
    nullptr,
    boost::mpl::c_str<MPLString>::value,
    nullptr
  };
  if (!RegisterClassEx(&window_class)) {
    throw last_error("ウィンドウクラスの登録に失敗しました\n詳細：");
  }
}

template <typename MPLString>
window_handle create_window() {
  const HWND window = CreateWindow(boost::mpl::c_str<MPLString>::value, 
                                   "",
                                   kWindowStyle,
                                   CW_USEDEFAULT,
                                   CW_USEDEFAULT, 
                                   CW_USEDEFAULT,
                                   CW_USEDEFAULT,
                                   nullptr,
                                   nullptr,
                                   GetModuleHandle(nullptr),
                                   nullptr);
  if (!window) {
    throw last_error("ウィンドウの作成に失敗しました\n詳細：");
  }
  return window_handle(window);
}

inline 
void set_procedure(const window_handle &window, const WNDPROC procedure) {
  assert(window);
  SetLastError(0);
  if (!SetWindowLongPtr(window.get(), GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(procedure))) {
    if (GetLastError()) {
      throw last_error("プロシージャの設定に失敗しました\n詳細：");
    }
  }
}

inline
void show(const window_handle &window) {
  assert(window);
  ShowWindow(window.get(), SW_RESTORE);
}

inline
void hide(const window_handle &window) {
  assert(window);
  ShowWindow(window.get(), SW_HIDE);
}

inline
void set_caption(const window_handle &window, const string_piece &caption) {
  assert(window);
  SetWindowText(window.get(), caption.c_str());
}

inline
std::string caption(const window_handle &window) {
  assert(window);
  std::vector<char> buffer(GetWindowTextLength(window.get()) + 1);
  GetWindowText(window.get(), &buffer.front(), buffer.size());
  return std::string(buffer.begin(), buffer.end() - 1);
}

inline
void set_icon(const window_handle &window) {
  assert(window);
}

inline
void resize(const window_handle &window, const int width, const int height) {
  assert(window);
  RECT rect = {0, 0, width, height};
  if (!AdjustWindowRect(&rect, kWindowStyle, FALSE)) {
    throw last_error("ウィンドウサイズの取得に失敗しました\n詳細：");
  }
  SetWindowPos(window.get(), nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
}

inline
void move(const window_handle &window, const int y, const int x) {
  assert(window);
  SetWindowPos(window.get(), nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

inline
int width(const window_handle &window) {
  assert(window);
  RECT rect;
  GetClientRect(window.get(), &rect);
  return rect.right - rect.left;
}

inline
int height(const window_handle &window) {
  assert(window);
  RECT rect;
  GetClientRect(window.get(), &rect);
  return rect.bottom - rect.top;
}

inline
int x(const window_handle &window) {
  assert(window);
  RECT rect;
  GetWindowRect(window.get(), &rect);
  return rect.left;
}

inline
int y(const window_handle &window) {
  assert(window);
  RECT rect;
  GetWindowRect(window.get(), &rect);
  return rect.top;
}
}}