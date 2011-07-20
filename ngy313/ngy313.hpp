#ifndef NGY313_NGY313_HPP_
#define NGY313_NGY313_HPP_

#include <cstdint>
#include <string>
#include <ngy313/platform.hpp>
#include <ngy313/fwd.hpp>
#include <ngy313/string_wrap.hpp>
#include <ngy313/detail/ngy313.hpp>

namespace ngy313 {
template <typename Pred>
int run(Pred pred) {
  return detail::main_singleton::instance().main().run(pred);
}

inline
void quit() {
  detail::main_singleton::instance().main().quit();
}

inline
void sleep(std::uint32_t time) {
  detail::main_singleton::instance().main().sleep(time);
}

inline
void window_show() {
  detail::main_singleton::instance().window().show();
}

inline
void set_window_caption(const string_wrap &text) {
  detail::main_singleton::instance().window().set_caption(text);
}

template <typename Icon>
void set_window_icon(const basic_icon<Icon> &i) {
  detail::main_singleton::instance().window().set_icon(i);
}

inline
void move_window(int x, int y) {
  detail::main_singleton::instance().window().move(x, y);
}

inline
void resize_window(int width, int height) {
  detail::main_singleton::instance().window().resize(width, height);
}

inline
std::string window_caption() {
  return detail::main_singleton::instance().window().caption();
}

inline
int window_x() {
  return detail::main_singleton::instance().window().x();
}

inline
int window_y() {
  return detail::main_singleton::instance().window().y();
}

inline
int window_width() {
  return detail::main_singleton::instance().window().width();
}

inline
int window_height() {
  return detail::main_singleton::instance().window().height();
}

inline
void resize_screen(int width, int height) {
  detail::main_singleton::instance().graphic().resize(width, height);
}

template <typename Wrap>
void clear_screen(const basic_color_wrap<Wrap> &color) {
  detail::main_singleton::instance().graphic().clear_screen(color);
}

inline
std::uint32_t screen_pixel_color(int x, int y) {
  return detail::main_singleton::instance().graphic().pixel_color(x, y);
}

inline
void present() {
  detail::main_singleton::instance().graphic().present();
}

template <typename Drawable>
void draw(Drawable &&drawable) {
	detail::main_singleton::instance().graphic().draw(
      std::forward<Drawable>(drawable));
}

template <typename Scene>
void render(Scene scene) {
	const detail::scoped_render<detail::graphic_system>
	  	render(detail::main_singleton::instance().graphic());
	if (render.succeeded()) {
		scene();
	}
}
}

#endif
