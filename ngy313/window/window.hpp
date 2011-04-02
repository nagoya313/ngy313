#ifndef NGY313_WINDOW_WINDOW_HPP_
#define NGY313_WINDOW_WINDOW_HPP_
#include <cassert>
#include <ngy313/window/detail/singleton.hpp>

namespace ngy313 { namespace window {
inline
void show() {
  detail::window().show();
}

inline
void hide() {
  detail::window().hide();
}

inline
std::string caption() {
  return detail::window().caption();
}

inline
void set_caption(const utility::string_piece &text) {
  detail::window().set_caption(text);
  assert(text.string() == caption());
}

inline
void set_icon() {
  detail::window().set_icon();
}

inline
int x() {
  return detail::window().x();
}

inline
int y() {
  return detail::window().y();
}

inline
void move(const int x_pos, const int y_pos) {
  detail::window().move(x_pos, y_pos);
  assert(x_pos == x());
  assert(y_pos == y());
}

inline
int width() {
  return detail::window().width();
}

inline
int height() {
  return detail::window().height();
}

inline
void resize(const int width_size, const int height_size) {
  detail::window().resize(width_size, height_size);
  assert(width_size == width());
  assert(height_size == height());
}
}}

#endif

