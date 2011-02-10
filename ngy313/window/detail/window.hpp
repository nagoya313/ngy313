#pragma once
#include <cassert>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <boost/mpl/string.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <Windows.h>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/fwd.hpp>

namespace ngy313 { namespace window { namespace detail {
// こいつらも公開していいものと非公開でもいいものがある
const std::uint32_t kWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

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
    // GetLastErrorは引数の所で呼ぶとまずいかもしれない？
    const DWORD error = GetLastError();
    throw boost::system::system_error(boost::system::error_code(error, boost::system::system_category()),
                                      "ウィンドウクラスの登録に失敗しました。\n詳細");
  }
}

template <typename MPLString>
handle create_window() {
  const handle window = CreateWindow(boost::mpl::c_str<MPLString>::value, 
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
    throw boost::system::system_error(boost::system::error_code(error, boost::system::system_category()),
                                      "ウィンドウの作成に失敗しました。\n詳細");
  }
  return window;
}

inline 
void set_procedure(const handle &window, const WNDPROC procedure) {
  assert(window);
  SetLastError(0);
  if (!SetWindowLongPtr(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(procedure))) {
    const DWORD error = GetLastError();
    if (error) {
      throw boost::system::system_error(boost::system::error_code(error, boost::system::system_category()),
                                        "プロシージャの設定に失敗しました。\n詳細");
    }
  }
}

inline
void show(const handle &window) {
  assert(window);
  ShowWindow(window, SW_RESTORE);
}

inline
void hide(const handle &window) {
  assert(window);
  ShowWindow(window, SW_HIDE);
}

inline
void set_caption(const handle &window, const utility::string_piece &caption) {
  assert(window);
  SetWindowText(window, caption.c_str());
}

inline
std::string caption(const handle &window) {
  assert(window);
  std::vector<char> buffer(GetWindowTextLength(window) + 1);
  GetWindowText(window, &buffer.front(), buffer.size());
  return std::string(buffer.begin(), buffer.end() - 1);
}

inline
void set_icon(const handle &window) {
  assert(window);
}

inline
void resize(const handle &window, const int width, const int height) {
  assert(window);
  RECT rect = {0, 0, width, height};
  if (!AdjustWindowRect(&rect, kWindowStyle, FALSE)) {
    const DWORD error = GetLastError();
    throw boost::system::system_error(boost::system::error_code(error, boost::system::system_category()),
                                      "ウィンドウサイズの取得に失敗しました。\n詳細");
  }
  SetWindowPos(window, nullptr, 0, 0, rect.right - rect.left, rect.bottom - rect.top, SWP_NOMOVE | SWP_NOZORDER);
}

inline
void move(const handle &window, const int y, const int x) {
  assert(window);
  SetWindowPos(window, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER);
}

inline
RECT client_rect(const handle &window) {
  assert(window);
  RECT rc;
  GetClientRect(window, &rc);
  return rc;
}

inline
int width(const handle &window) {
  assert(window);
  RECT rect = client_rect(window);
  return rect.right - rect.left;
}

inline
int height(const handle &window) {
  assert(window);
  RECT rect = client_rect(window);
  return rect.bottom - rect.top;
}

inline
RECT rect(const handle &window) {
  assert(window);
  RECT rc;
  GetWindowRect(window, &rc);
  return rc;
}

inline
int x(const handle &window) {
  assert(window);
  return rect(window).left;
}

inline
int y(const handle &window) {
  assert(window);
  return rect(window).top;
}
}}}
