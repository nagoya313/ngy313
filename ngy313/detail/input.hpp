#pragma once
#include "window_singleton.hpp"

namespace ngy313 { namespace detail {
inline
bool pressed(const int key) {
  return GetAsyncKeyState(key) < 0;
}
}}