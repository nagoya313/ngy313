#pragma once
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/iteration.hpp>
#include <pstade/oven/taken_while.hpp>
#include <Windows.h>

namespace ngy313 {
inline
pstade::oven::any_range<int, boost::forward_traversal_tag> process_message() {
  return pstade::oven::iteration(0, [](int) -> int {
    MSG message;
    return PeekMessage(&message, nullptr, 0, 0, PM_NOREMOVE);
  }) | pstade::oven::taken_while([](const int x) -> bool {
    if (x) {
      MSG message;
      const BOOL result = GetMessage(&message, nullptr, 0, 0);
      if (!(result && ~result)) {
        return false;
      } else {
        TranslateMessage(&message);
        DispatchMessage(&message);
      }
    }
    return true;
  });
}
}
