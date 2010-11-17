#pragma once
#include <cassert>
#include <cstdint>
#include <memory>
#include <Windows.h>

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

typedef std::unique_ptr<std::remove_pointer<HWND>::type, window_delete> 
    window_handle;

const std::uint32_t kWindowStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX;
}}