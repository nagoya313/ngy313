#pragma once
#include <cstdint>
#include <Windows.h>
#include "input.hpp"

namespace ngy313 { namespace detail {
inline
int run(const std::function<void ()> work) {
  MSG mes;
  for (;;) {
    if (PeekMessage(&mes, nullptr, 0, 0, PM_NOREMOVE)) {
      const BOOL result = GetMessage(&mes, nullptr, 0, 0);
      if (!(result && ~result)) {
        break;
      } 
      TranslateMessage(&mes);
      DispatchMessage(&mes);
    } else {
      input_callback()();
      work();
    }
  }
  return mes.wParam;
}

inline
void post_quit_message(const int code) {
  PostQuitMessage(code);
}

inline 
void sleep(const std::uint32_t time) {
  Sleep(time);
}
}}