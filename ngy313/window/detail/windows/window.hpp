#pragma once
#include <cassert>
#include <string>
#include <system_error>
#include <CommCtrl.h>
#include <Windows.h>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/windows/fwd.hpp>

namespace ngy313 { namespace window { namespace detail {
// こいつらも公開していいものと非公開でもいいものがある
const DWORD kWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

inline
void regist_window_class(const utility::string_piece &name) {
  const WNDCLASSEXA window_class  = {
    sizeof(window_class),
    CS_HREDRAW | CS_VREDRAW,
    &DefWindowProc,
    0,
    0,
    GetModuleHandle(nullptr),
    reinterpret_cast<HICON>(LoadImage(nullptr, 
                                      IDI_APPLICATION, 
                                      IMAGE_ICON, 
                                      32,
                                      32,
                                      LR_DEFAULTSIZE | LR_SHARED)),
    reinterpret_cast<HCURSOR>(LoadImage(nullptr,
                                        IDC_ARROW, 
                                        IMAGE_CURSOR, 
                                        0,
                                        0,
                                        LR_DEFAULTSIZE | LR_SHARED)),
    reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
    nullptr,
    name.c_str(),
    nullptr
  };
  if (!RegisterClassExA(&window_class)) {
    // GetLastErrorは引数の所で呼ぶとまずいかもしれない？
    const DWORD error = GetLastError();
    throw std::system_error(std::error_code(error, std::system_category()),
                            "ウィンドウクラスの登録に失敗しました。\n詳細");
  }
}

inline
handle create_window(const utility::string_piece &name) {
  const handle window = CreateWindowA(name.c_str(), 
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
  if (!SetWindowLongPtrA(window, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(procedure))) {
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
RECT client_rect(const handle window) {
  assert(window);
  RECT rc;
  GetClientRect(window, &rc);
  return rc;
}

inline
RECT rect(const handle window) {
  assert(window);
  RECT rc;
  GetWindowRect(window, &rc);
  return rc;
}
}}}
