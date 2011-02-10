#pragma once
#pragma comment(lib, "XInput.lib")
#include <cassert>
#include <cstdint>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <Windows.h>
#include <XInput.h>

namespace ngy313 { namespace input { namespace detail {
inline
bool pressed(const int key) {
  return GetAsyncKeyState(key) < 0;
}
}}}

namespace ngy313 { namespace input { namespace mouse { namespace detail {
inline
void enable_disp(const bool enable) {
  ShowCursor(enable);
}

inline
POINT position() {
  POINT point;
  if (!GetCursorPos(&point)) {
    const DWORD error = GetLastError();
    throw boost::system::system_error(boost::system::error_code(error, boost::system::system_category()),
                                      "マウスの位置の取得に失敗しました。\n詳細");
  }
  return point;
}

inline
int x() {
  return position().x;
}

inline
int y() {
  return position().y;
}

inline
void move(const int x, const int y) {
  if (!SetCursorPos(x, y)) {
    const DWORD error = GetLastError();
    throw boost::system::system_error(boost::system::error_code(error, boost::system::system_category()),
                                      "マウスの移動に失敗しました。\n詳細");
  }
}
}}}}

namespace ngy313 { namespace input { namespace joypad { namespace detail {
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
