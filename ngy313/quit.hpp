#pragma once
#include <Windows.h>

namespace ngy313 {
inline
void quit() {
  PostQuitMessage(0);
}
}
