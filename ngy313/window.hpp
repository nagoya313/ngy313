#pragma once
#include <string>
#include <vector>
#include "detail/window_fwd.hpp"

namespace ngy313 {
inline
void window_show() {
  assert(detail::get_window_handle());
  ShowWindow(detail::get_window_handle().get(), SW_RESTORE);
}

inline
void window_hide() {
  assert(detail::get_window_handle());
  ShowWindow(detail::get_window_handle().get(), SW_HIDE);
}

inline
void set_window_caption(const std::string &caption) {
  assert(detail::get_window_handle());
  SetWindowText(detail::get_window_handle().get(), caption.c_str());
}

inline
void set_window_icon() {
  assert(detail::get_window_handle());
}

inline
void window_move(const int x, const int y) {
  assert(detail::get_window_handle());
  SetWindowPos(detail::get_window_handle().get(), 
               nullptr, 
               x, 
               y,
               0,
               0,
               SWP_NOSIZE | SWP_NOZORDER);
}

void window_resize(const int width, const int height) {
  assert(detail::get_window_handle());
  RECT rect = {
    0, 0, width, height
  };
  if (!AdjustWindowRect(&rect, detail::kWindowStyle, FALSE)) {
    throw detail::last_error("fails in the acquisition of the size of the window");
  }
  SetWindowPos(detail::get_window_handle().get(), 
               nullptr,
               0,
               0,
               rect.right - rect.left,
               rect.bottom - rect.top, 
               SWP_NOMOVE | SWP_NOZORDER);
}

std::string window_caption() {
  assert(detail::get_window_handle());
  std::vector<char> buffer(GetWindowTextLength(
                               detail::get_window_handle().get()) + 1);
  GetWindowText(detail::get_window_handle().get(), 
                &buffer.front(), buffer.size());
  return std::string(buffer.begin(), buffer.end() - 1);
}

int window_x() {
  assert(detail::get_window_handle());
  RECT rect;
  GetWindowRect(detail::get_window_handle().get(), &rect);
  return rect.left;
}

int window_y() {
  assert(detail::get_window_handle());
  RECT rect;
  GetWindowRect(detail::get_window_handle().get(), &rect);
  return rect.top;
}

int window_width() {
  assert(detail::get_window_handle());
  RECT rect;
  GetClientRect(detail::get_window_handle().get(), &rect);
  return rect.right - rect.left;
}

int window_height() {
  assert(detail::get_window_handle());
  RECT rect;
  GetClientRect(detail::get_window_handle().get(), &rect);
  return rect.bottom - rect.top;
}
}