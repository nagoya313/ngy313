#ifndef NGY313_WINDOW_DETAIL_LINUX_MAIN_WINDOW_HPP_
#define NGY313_WINDOW_DETAIL_LINUX_MAIN_WINDOW_HPP_
#include <cassert>
#include <functional>
#include <memory>
#include <string>
#include <boost/noncopyable.hpp>
#include <gtkmm.h>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/process/detail/linux/initializer.hpp>

namespace ngy313 { namespace window { namespace detail {
class main_window : private boost::noncopyable {
 public:
  main_window() : init_(), window_(), func_([] {}), icon_("default_icon") {
    window_.set_resizable(false);
  }

  void show() {
    window_.show();
  }

  void hide() const {
  }

  void set_caption(const utility::string_piece &text) {
    window_.set_title(text.c_str());
    assert(text.string() == caption());
  }

  void set_icon(const utility::string_piece &icon_name) {
    window_.set_icon(Gdk::Pixbuf::create_from_file(icon_name.string()));
    icon_ = icon_name.string();
    assert(icon() == icon_name.string());
  }
  
  std::string icon() const {
    return icon_;
  }

  void move(const int x_pos, const int y_pos) {
    window_.move(x_pos, y_pos);
    assert(x() == x_pos);
    assert(y() == y_pos);
  }

  void resize(const int width_size, const int height_size) {
    Gdk::Geometry size;
    width_ = size.min_width = width_size;
    height_ = size.min_height = height_size;
    window_.set_geometry_hints(window_, size, Gdk::HINT_MIN_SIZE);
    window_.resize(width_size, height_size);
    assert(width() == width_size);
    assert(height() == height_size);
  }

  std::string caption() const {
    return window_.get_title();
  }

  int x() const {
    int x;
    int y;
    window_.get_position(x, y);
    return x;
  }

  int y() const {
    int x;
    int y;
    window_.get_position(x, y);
    return y;
  }

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }
  
  template <typename Device>
  void set_graphic_device(Device &device) {
    window_.add(device);
    window_.show_all_children();
  }
  
  template <typename Pred>
  void set_func(const Pred pred) {
    func_ = pred;
    Glib::signal_timeout().connect(sigc::mem_fun(*this, &main_window::update), 16);
  }

  Gtk::Window &window() {
    return window_;
  }

 private:
  bool update() {
    func_();
    return true;
  }
  
  const class window_initializer : private boost::noncopyable {
   public:
    window_initializer() : kit_(process::detail::initializer::instance().kit()) {}
  
   private:
   std::unique_ptr<Gtk::Main> &kit_;
  } init_;
  Gtk::Window window_;
  std::function<void ()> func_;
  int width_;
  int height_;
  std::string icon_;
};
}}}

#endif
