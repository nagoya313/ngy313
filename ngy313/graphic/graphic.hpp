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
  detail::clear(detail::device(), col);
}

inline
void present() {
  detail::present();
}

inline
std::uint32_t pixel_color(const float x, const float y) {
  return detail::pixel_color(detail::device(), x, y);
}

inline
void resize(const int width, const int height) {
  detail::resize(width, height);
}

inline
int width() {
  return detail::width();
}

inline
int height() {
  return detail::height();
}

inline
void change_screen_mode(const screen_mode flag) {
  detail::change_screen_mode(flag == kWindowMode ? true : false);
}

template <typename Drawable>
void draw(const Drawable &drawable) {
  const detail::draw<Drawable> draw(detail::device(), drawable);
}
}}
