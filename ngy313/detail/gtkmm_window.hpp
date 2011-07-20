#ifndef NGY313_DETAIL_GTKMM_MAIN_WINDOW_HPP_
#define NGY313_DETAIL_GTKMM_MAIN_WINDOW_HPP_

#include <cassert>
#include <memory>
#include <string>
#include <gtkmm.h>
#include <ngy313/fwd.hpp>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
class gtkmm_window {
 public:
  class window_impl : public Gtk::Window {
	 public:
	  window_impl() {
	    set_resizable(false);
	  }
	 
   protected:
    virtual bool on_delete_event(GdkEventAny *event) {
	    Gtk::Main::quit();
	    return true;
    }
  };
  
  typedef const std::unique_ptr<window_impl> &handle_type;

  gtkmm_window() : handle_(new window_impl()),
  		              width_(640),
  		              height_(480) {
    resize(width_, height_);  
  }

  void show() {
    handle_->show();
  }

  void set_caption(const string_wrap &text) {
    handle_->set_title(text.c_str());
    assert(text.string() == caption());
  }

  template <typename Icon>
  void set_icon(const basic_icon<Icon> &icon) {
    handle_->set_icon(icon.handle());
  }

  void move(int x_pos, int y_pos) {
    handle_->move(x_pos, y_pos);
    assert(x() == x_pos && y() == y_pos);
  }

  void resize(int width_size, int height_size) {
    Gdk::Geometry size;
    width_ = size.min_width = width_size;
    height_ = size.min_height = height_size;
    handle_->set_geometry_hints(*handle_, size, Gdk::HINT_MIN_SIZE);
    handle_->resize(width_size, height_size);
    assert(width() == width_size && height() == height_size);
  }

  std::string caption() const {
    return handle_->get_title();
  }

  int x() const {
    int x;
    int y;
    handle_->get_position(x, y);
    return x;
  }

  int y() const {
    int x;
    int y;
    handle_->get_position(x, y);
    return y;
  }

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }
  
  handle_type handle() const {
    return handle_;
  }

 private:
  std::unique_ptr<window_impl> handle_;
  int width_;
  int height_;
};
}}

#endif
