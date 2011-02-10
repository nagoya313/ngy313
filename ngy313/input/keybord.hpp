#pragma once
#include <cstdint>
#include <array>
#include <ngy313/input/detail/input.hpp>

namespace ngy313 { namespace input { namespace keybord {
enum key_code {
  // ‚Ü‚¾‘«‚è‚È‚¢
  kDown = VK_DOWN,
  kUp = VK_UP,
  kLeft = VK_LEFT,
  kRight = VK_RIGHT,
  kReturn = VK_RETURN,
  kShift = VK_SHIFT,
  kSpace = VK_SPACE,
  kEscape = VK_ESCAPE,
  kDelete = VK_DELETE,
  kBackSpace = VK_BACK,
  kTab = VK_TAB,
  kControl = VK_CONTROL,
  kAlt = VK_MENU,
  kF1 = VK_F1,
  kF2 = VK_F2,
  kF3 = VK_F3,
  kF4 = VK_F4,
  kF5 = VK_F5,
  kF6 = VK_F6,
  kF7 = VK_F7,
  kF8 = VK_F8,
  kF9 = VK_F9,
  kF10 = VK_F10,
  kF11 = VK_F11,
  kF12 = VK_F12,
  kA = 'A',
  kB = 'B',
  kC = 'C',
  kD = 'D',
  kE = 'E',
  kF = 'F',
  kG = 'G',
  kH = 'H',
  kI = 'I',
  kJ = 'J',
  kK = 'K',
  kL = 'L',
  kM = 'M',
  kN = 'N',
  kO = 'O',
  kP = 'P',
  kQ = 'Q',
  kR = 'R',
  kS = 'S',
  kT = 'T',
  kU = 'U',
  kV = 'V',
  kW = 'W',
  kX = 'X',
  kY = 'Y',
  kZ = 'Z'
};

inline
bool key_pressed(const key_code key) {
  return ngy313::input::detail::pressed(key);
}

inline
std::array<std::uint8_t, 256> all_key_state() {
  std::array<std::uint8_t, 256> key_state;
  GetKeyboardState(&key_state.front());
  return key_state;
}

inline
void set_all_key_state(const std::array<std::uint8_t, 256> &state) {
  std::array<std::uint8_t, 256> temp = state;
  SetKeyboardState(&temp.front());
}
}}}
