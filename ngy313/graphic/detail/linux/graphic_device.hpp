#ifndef NGY313_GRAPHIC_DETAIL_LINUX_GRAPHIC_DEVICE_HPP_
#define NGY313_GRAPHIC_DETAIL_LINUX_GRAPHIC_DEVICE_HPP_
#include <cassert>
#include <cstdint>
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <GL/glew.h>
#include <gtkglmm.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <ngy313/graphic/detail/linux/device.hpp>
#include <ngy313/window/detail/linux/main_window.hpp>
#include <ngy313/utility/call_once.hpp>
#include <iostream>

namespace ngy313 { namespace graphic { namespace detail {
class device_handle : public Gtk::GL::DrawingArea {
 public:
  device_handle(window::detail::main_window &window) : init_(&gl_init), width_(window.width()), height_(window.height()) {
    const Glib::RefPtr<Gdk::GL::Config> glconfig = Gdk::GL::Config::create(Gdk::GL::MODE_RGB | Gdk::GL::MODE_DEPTH | Gdk::GL::MODE_DOUBLE);
    if (!glconfig) {
      throw std::runtime_error("OpenGLÇÃèâä˙âªÇ…é∏îsÇµÇ‹ÇµÇΩ");
    }
    set_gl_capability(glconfig);
    window.set_graphic_device(*this);
  }
  
  bool begin_scene() {
    const Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    return glwindow->gl_begin(get_gl_context());
  }

  void end_scene() {
    const Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    glwindow->gl_end();
  }
  
  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }
  
 private:  
  virtual bool on_configure_event (GdkEventConfigure * const event) {
    const Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window ();
    glwindow->gl_begin(get_gl_context ());
    glViewport(0, 0, width_, height_);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.f, static_cast<float>(width_), static_cast<float>(height_), 0.f, 0.f, 1.f);
    glwindow->gl_end ();
    return true;
  }

  virtual void on_realize() {
    Gtk::DrawingArea::on_realize();
  }
  
  virtual bool on_expose_event(GdkEventExpose * const event) {
    const Glib::RefPtr<Gdk::GL::Window> glwindow = get_gl_window();
    glwindow->gl_begin(get_gl_context());
    glwindow->swap_buffers ();
    glwindow->gl_end();
    return true;
  }
  
  const utility::call_once init_;
  int width_;
  int height_;
};

class graphic_device : private boost::noncopyable {
 public:
  explicit graphic_device(window::detail::main_window &window)
      : device_(window),
        windowed_(true),
        width_(window.width()),
        height_(window.height()) {}

  bool windowed() const {
    return windowed_;
  }

  void present() {
    const Glib::RefPtr<Gdk::GL::Window> glwindow = device_.get_gl_window();
    glwindow->swap_buffers();
  }

  void resize(const int width_size, const int height_size) {
    width_ = width_size;
    height_ = height_size;
    assert(width_size == width());
    assert(height_size == height());
  }

  void change_screen_mode(const bool flag) {
    windowed_ = flag;
    reset();
    assert(windowed() == flag);
  }

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

  void clear(const std::uint32_t col) {
    const float f = 1.f / 255.f;
    glClearColor(f * static_cast<float>(static_cast<std::uint8_t>(col >> 16)), 
                 f * static_cast<float>(static_cast<std::uint8_t>(col >> 8)),
                 f * static_cast<float>(static_cast<std::uint8_t>(col)),
                 f * static_cast<float>(static_cast<std::uint8_t>(col >> 24)));
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  bool begin_scene() {
    const Glib::RefPtr<Gdk::GL::Window> glwindow = device_.get_gl_window();
    return glwindow->gl_begin(device_.get_gl_context());
  }

  void end_scene() {
    const Glib::RefPtr<Gdk::GL::Window> glwindow = device_.get_gl_window();
    glwindow->gl_end();
  }

  std::uint32_t pixel_color(const int x, const int y) const {
    std::uint8_t pixel[3];
    glReadBuffer(GL_BACK);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, pixel);
    std::uint32_t result = 0xFF << 24 | pixel[0] << 16 | pixel[1] << 8 | pixel[2]; 
    std::cout << "(" << x << "," << y << ")" << (int)pixel[0] << "," << (int)pixel[1] << "," << (int)pixel[2] << std::endl;
    return result;
  }

  device_handle &device() {
    return device_;
  }

  //boost::signals2::signal<void (const device_handle &)> before_reset;

  //boost::signals2::signal<void (const device_handle &)> after_reset;
  
 private:
  void reset() const {
  }
  
  device_handle device_;
  bool windowed_;
  int width_;
  int height_;
};
}}}

#endif

