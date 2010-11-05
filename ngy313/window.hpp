#pragma once
#include <string>
#include <vector>
#include "detail/window_singleton.hpp"
#include "detail/window_impl.hpp"

namespace ngy313 {
inline
void window_show() {
  detail::show(detail::window());
}

inline
void window_hide() {
  detail::hide(detail::window());
}

inline
void set_window_caption(const string_piece &caption) {
  detail::set_caption(detail::window(), caption);
}

inline
void set_window_icon() {
  detail::set_icon(detail::window());
}

inline
void window_move(const int x, const int y) {
  detail::move(detail::window(), x, y);
}

void window_resize(const int width, const int height) {
  detail::resize(detail::window(), width, height);
  detail::reset(detail::window(), detail::graphic_device(), true);
}

std::string window_caption() {
  return detail::caption(detail::window());
}

int window_x() {
  return detail::x(detail::window());
}

int window_y() {
  return detail::y(detail::window());
}

int window_width() {
  return detail::width(detail::window());
}

int window_height() {
  return detail::height(detail::window());
}
}