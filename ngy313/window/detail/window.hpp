#pragma once
#include <cassert>
#include <string>
#include <system_error>
#include <vector>
#include <CommCtrl.h>
#include <Windows.h>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/fwd.hpp>

namespace ngy313 { namespace window { namespace detail {
// こいつらも公開していいものと非公開でもいいものがある
const DWORD kWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

inline
void regist_window_class(const utility::string_piece &name) {
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
    name.c_str(),
    nullptr
  };
  if (!RegisterClassEx(&window_class)) {
    // GetLastErrorは引数の所で呼ぶとまずいかもしれない？
    const DWORD error = GetLastError();
    throw std::system_error(std::error_code(error, std::system_category()),
                            "ウィンドウクラスの登録に失敗しました。\n詳細");
  }
}

inline
handle create_window(const utility::string_piece &name) {
  const handle window = CreateWindow(name.c_str(), 
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
    const DWORD error = GetLastError();
    throw std::system_error(std::error_code(error, std::system_category()), "ウィンドウの作成に失敗しました。\n詳細");
  }
  return window;
}

inline 
void set_procedure(const handle window, const WNDPROC procedure) {
  assert(window);
  SetLastError(0);
  if (!SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(procedure))) {
    const DWORD error = GetLastError();
    if (error) {
      throw std::system_error(std::error_code(error, std::system_category()),
                              "プロシージャの設定に失敗しました。\n詳細");
    }
  }
}

inline 
void set_subclass_procedure(const handle window, const UINT_PTR id, const SUBCLASSPROC procedure) {
  assert(window);
  if (!SetWindowSubclass(window, procedure, id, 0)) {
    const DWORD error = GetLastError();
    throw std::system_error(std::error_code(error, std::system_category()),
                            "サブクラスプロシージャの設定に失敗しました。\n詳細");
  }
}

inline
void show(const handle window) {
  assert(window);
  ShowWindow(window, SW_RESTORE);
}

inline
void hide(const handle window) {
  assert(window);
  ShowWindow(window, SW_HIDE);
}

inline
std::string caption(const handle window) {
  assert(window);
  std::vector<char> buffer(GetWindowTextLength(window) + 1);
  GetWindowText(window, buffer.data(), buffer.size());
  return std::string(buffer.begin(), buffer.end() - 1);
}

inline
void set_caption(const handle window, const utility::string_piece &text) {
  assert(window);
  SetWindowText(window, text.c_str());
  assert(text.c_str() == caption(window));
}

inline
void set_icon(const handle window) {
  assert(window);
}

inline
RECT client_rect(const handle window) {
  assert(window);
  RECT rc;
  GetClientRect(window, &rc);
  return rc;
}

inline
int width(const handle window) {
  assert(window);
  RECT rect = client_rect(window);
  return rect.right - rect.left;
}

inline
int height(const handle window) {
  assert(window);
  RECT rect = client_rect(window);
  return rect.bottom - rect.top;
}

inline
void resize(const handle window, const int width_size, const int height_size) {
  assert(window);
  RECT rect = {0, 0, width_size, height_size};
  if (!AdjustWindowRect(&rect, kWindowStyle, FALSE)) {
    const DWORD error = GetLastError();
    throw std::system_error(std::error_code(error, std::system_category()),
                            "ウィンドウサイズの取得に失敗しました。\n詳細");
  }
  SetWindowPos(window, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
  assert(width_size == width(window));
  assert(height_size == height(window));
}

inline
RECT rect(const handle window) {
  assert(window);
  RECT rc;
  GetWindowRect(window, &rc);
  return rc;
}

inline
int x(const handle window) {
  assert(window);
  return rect(window).left;
}

inline
int y(const handle window) {
  assert(window);
  return rect(window).top;
}

inline
void move(const handle window, const int x_pos, const int y_pos) {
  assert(window);
  SetWindowPos(window, nullptr, x_pos, y_pos, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
  assert(x_pos == x(window));
  assert(y_pos == y(window));
}
}}}
