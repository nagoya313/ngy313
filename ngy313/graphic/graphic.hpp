#pragma once
#include <ngy313/graphic/detail/draw.hpp>
#include <ngy313/graphic/detail/singleton.hpp>
#include <ngy313/window/window.hpp>

namespace ngy313 { namespace graphic {
enum screen_mode {
  kWindowMode, 
  kFullscreenMode
};

inline
void clear_screen(const std::uint32_t col) {
  detail::device().clear(col);
}

inline
void present() {
  detail::device().present();
}

inline
std::uint32_t pixel_color(const float x, const float y) {
  return detail::device().pixel_color(x, y);
}

inline
void resize(const int width, const int height) {
  detail::device().resize(width, height);
}

inline
int width() {
  return detail::device().width();
}

inline
int height() {
  return detail::device().height();
}

inline
void change_screen_mode(const screen_mode flag) {
  detail::device().change_screen_mode(flag == kWindowMode ? true : false);
}

template <typename Drawable>
void draw(const Drawable &drawable) {
  const detail::draw<Drawable> draw(detail::device().device(), drawable);
}
}}
