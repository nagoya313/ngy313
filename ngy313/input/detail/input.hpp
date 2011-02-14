#pragma once
#include <Windows.h>


namespace ngy313 { namespace input { namespace detail {
inline
bool pressed(const int key) {
  return GetAsyncKeyState(key) < 0;
}
}}}
