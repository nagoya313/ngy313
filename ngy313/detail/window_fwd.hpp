#pragma once
#include <cassert>
#include <cstdint>
#include <memory>
#include <Windows.h>
#include "singleton.hpp"
#include "last_error.hpp"

namespace ngy313 { namespace detail {
struct mutex_delete {
  void operator ()(const HANDLE mutex) const {
    assert(mutex);
    CloseHandle(mutex);
  }
};

typedef std::unique_ptr<std::remove_pointer<HANDLE>::type, mutex_delete> mutex_handle;

struct window_delete {
  void operator ()(const HWND window) const {
    assert(window);
    DestroyWindow(window);
  }
};

typedef std::unique_ptr<std::remove_pointer<HWND>::type, window_delete> window_handle;

const std::uint32_t kWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;

LRESULT CALLBACK window_procedure(const HWND window_handle, const UINT message, const WPARAM wp, const LPARAM lp) {
  if (message == WM_CLOSE) {
    PostQuitMessage(0);
    return 0;
  }
  return DefWindowProc(window_handle, message, wp, lp);
}

class window_singleton : public singleton<window_singleton> {
 public:
  const window_handle &handle() const {
    return window_handle_;
  }

 private:
  window_singleton() : window_handle_(create_window()) {}

  static window_handle create_window() {
    const char * const kClassName = "BASE";
    const WNDCLASSEX window_class  = {
      sizeof(window_class),
      CS_HREDRAW | CS_VREDRAW,
      &window_procedure,
      0,
      0,
      GetModuleHandle(nullptr),
      reinterpret_cast<HICON>(LoadImage(nullptr, MAKEINTRESOURCE(IDI_APPLICATION), IMAGE_ICON, 32, 32, LR_DEFAULTSIZE | LR_SHARED)),
      reinterpret_cast<HCURSOR>(LoadImage(nullptr, MAKEINTRESOURCE(IDC_ARROW), IMAGE_CURSOR, 0, 0, LR_DEFAULTSIZE | LR_SHARED)),
      reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
      nullptr,
      kClassName,
      nullptr
    };
    if (!RegisterClassEx(&window_class)) {
      throw last_error("fails in the registration of the window class");
    }
    const HWND handle = CreateWindow("BASE", 
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
    if (!handle) {
      throw last_error("fails in making the window");
    }
    return window_handle(handle);
  }

  const window_handle window_handle_;
  friend singleton<window_singleton>;
};

const window_handle &get_window_handle() {
  return window_singleton::instance().handle();
}
}}