#pragma once
#include <ngy313/window/detail/singleton.hpp>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace window {
inline
void show() {
  detail::show(detail::window());
}

inline
void hide() {
  detail::hide(detail::window());
}

inline
void set_caption(const utility::string_piece &caption) {
  detail::set_caption(detail::window(), caption);
}

inline
void set_icon() {
  detail::set_icon(detail::window());
}

inline
void move(const int x, const int y) {
  detail::move(detail::window(), x, y);
}

inline
void resize(const int width, const int height) {
  detail::resize(detail::window(), width, height);
}

inline
std::string caption() {
  return detail::caption(detail::window());
}

inline
int x() {
  return detail::x(detail::window());
}

inline
int y() {
  return detail::y(detail::window());
}

inline
int width() {
  return detail::width(detail::window());
}

inline
int height() {
  return detail::height(detail::window());
}
}}
