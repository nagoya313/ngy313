#pragma once
#pragma comment(lib, "XInput.lib")
#include <cassert>
#include <cstdint>
#include <XInput.h>

namespace ngy313 { namespace input { namespace joypad { namespace detail {
const int kDeadZoneLeftX = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
const int kDeadZoneLeftY = XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
const int kDeadZoneRightX = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
const int kDeadZoneRightY = XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

inline
XINPUT_STATE state(const int num) {
  assert(num >= 0 && num <= 3);
  XINPUT_STATE st;
  XInputGetState(num, &st);
  return st;
}

inline
bool pressed(const int num, const std::uint32_t code) {
  assert(num >= 0 && num <= 3);
  XINPUT_STATE st = state(num);
  return (st.Gamepad.wButtons & code) != 0;
}

inline
bool connected(const int num) {
  assert(num >= 0 && num <= 3);
  XINPUT_STATE st;
  return XInputGetState( 0, &st) == ERROR_SUCCESS;
}
}}}}
