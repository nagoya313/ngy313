#pragma once
#include <cassert>
#include <array>
#include <boost/range/algorithm/count.hpp>
#include <ngy313/input/detail/joypad.hpp>

namespace ngy313 { namespace input { namespace joypad {
// R21‚ÆL2‚ð‚Ç‚¤‚·‚é‚©
enum key_code {
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

class pad_state {
 public:
  explicit pad_state(const int num) : state_(detail::state(num).Gamepad) {}

  bool key_pressed(const key_code key) const {
    return (state_.wButtons & key) != 0;
  }

  int analog_input_left_x() const {
    const int value = state_.sThumbLX;
    return value < detail::kDeadZoneLeftX && value > -detail::kDeadZoneLeftX ? 0 : value;
  }

  int analog_input_left_y() const {
    const int value = state_.sThumbLY;
    return value < detail::kDeadZoneLeftY && value > -detail::kDeadZoneLeftY ? 0 : value;
  }

  int analog_input_right_x() const {
    const int value = state_.sThumbRX;
    return value < detail::kDeadZoneRightX && value > -detail::kDeadZoneRightX ? 0 : value;
  }

  int analog_input_right_y() const {
    const int value = state_.sThumbRY;
    return value < detail::kDeadZoneRightY && value > -detail::kDeadZoneRightY ? 0 : value;
  }

 private:
  const XINPUT_GAMEPAD state_;
};

struct key_data {
  int num;
  key_code code;
};

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
