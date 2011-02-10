#pragma once
#include <ngy313/input/detail/input.hpp>

namespace ngy313 { namespace input { namespace mouse {
enum key_code {
  kLButton = VK_LBUTTON,
  kRButton = VK_RBUTTON,
  kMButton = VK_MBUTTON
};

inline
void enable_disp(const bool enable) {
  detail::enable_disp(enable);
}

inline
int x() {
  return detail::x();
}

inline
int y() {
  return detail::y();
}

inline
void move(const int x, const int y) {
  detail::move(x, y);
}

inline
bool key_pressed(const key_code key) {
  // 予定メモ：物理と論理をひっくり返すようにする
  // GetSystemMetrics(SM_SWAPBUTTON); を使う
  return ngy313::input::detail::pressed(key);
}
}}}
