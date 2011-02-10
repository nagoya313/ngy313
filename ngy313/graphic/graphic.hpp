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
  detail::present(detail::device(), true, detail::before_reset(), detail::after_reset());
}

inline
std::uint32_t pixel_color(const float x, const float y) {
  // ������
  return 0;
}

inline
void resize(const int width, const int height) {
  // �X�N���[�����[�h�ێ���������
  detail::reset(detail::device(), true, width, height, detail::before_reset(), detail::after_reset());
}

inline
int width() {
  // �����Ǝ�������
  return window::width();
}

inline
int height() {
  // �����Ǝ�������
  return window::height();
}

inline
void change_screen_mode(const screen_mode flag) {
  detail::reset(detail::device(), 
                flag == kWindowMode ? true : false,
                width(),
                height(),
                detail::before_reset(),
                detail::after_reset());
}

template <typename Drawable>
void draw(const Drawable &drawable) {
  const detail::draw<Drawable> draw(detail::device(), drawable);
}
}}
