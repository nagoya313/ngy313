#pragma once
#include <cstdint>
#include <functional>
#include <Windows.h>

namespace ngy313 { namespace process { namespace detail {
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
      work();
    }
  }
  return mes.wParam;
}

inline
void post_quit_message(const int code) {
  PostQuitMessage(code);
}

// crono‚ª—ˆ‚½‚ç‚à‚¤­‚µl‚¦‚é
inline 
void sleep(const std::uint32_t time) {
  Sleep(time);
}
}}}
