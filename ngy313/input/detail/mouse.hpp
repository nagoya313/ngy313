#pragma once
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <Windows.h>
#include <ngy313/window/detail/singleton.hpp>

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
  if (!ScreenToClient(window::detail::window(), &point)) {
    const DWORD error = GetLastError();
    throw boost::system::system_error(boost::system::error_code(error, boost::system::system_category()),
                                      "マウスの位置の変換に失敗しました。\n詳細");
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
