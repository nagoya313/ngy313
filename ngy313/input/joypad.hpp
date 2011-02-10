#pragma once
#include <cassert>
#include <array>
#include <boost/range/algorithm/count.hpp>
#include <ngy313/input/detail/input.hpp>

namespace ngy313 { namespace input { namespace joypad {
enum key_code {
  // R21‚ÆL2‚ð‚Ç‚¤‚·‚é‚©
  kDown = XINPUT_GAMEPAD_DPAD_DOWN,
  kUp = XINPUT_GAMEPAD_DPAD_UP,
  kLeft = XINPUT_GAMEPAD_DPAD_LEFT,
  kRight = XINPUT_GAMEPAD_DPAD_RIGHT,
  kStart = XINPUT_GAMEPAD_START,
  kBack = XINPUT_GAMEPAD_BACK,
  kLeftThumb = XINPUT_GAMEPAD_LEFT_THUMB,
  kRightThumb = XINPUT_GAMEPAD_RIGHT_THUMB,
  kLeftShoulder = XINPUT_GAMEPAD_LEFT_SHOULDER,
  kRightShoulder = XINPUT_GAMEPAD_RIGHT_SHOULDER,
  kA = XINPUT_GAMEPAD_A,
  kB = XINPUT_GAMEPAD_B,
  kX = XINPUT_GAMEPAD_X,
  kY = XINPUT_GAMEPAD_Y
};

struct key_data {
  int num;
  key_code code;
};

inline
bool key_pressed(const int num, const key_code key) {
  assert(num >= 0 && num <= 3);
  return detail::pressed(num, key);
}

inline
bool connected(const int num) {
  assert(num >= 0 && num <= 3);
  return detail::connected(num);
}

inline
int count() {
  // ‚¿‚å‚Á‚Æ–³—‚â‚è‚·‚¬‚é‚©
  const std::array<bool, 4> state = {connected(0), connected(1), connected(2), connected(3)};
  const int num = boost::count(state, true);
  assert(num >= 0 && num <= 3);
  return num;
}
}}}
