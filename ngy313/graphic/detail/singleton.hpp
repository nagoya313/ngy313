#pragma once
#include <boost/signals2/signal.hpp>
#include <ngy313/graphic/detail/device.hpp>
#include <ngy313/window/detail/singleton.hpp>

namespace ngy313 { namespace graphic { namespace detail {
class singleton : private boost::noncopyable {
 public:
  static singleton &instance() {
    static singleton graphic;
    return graphic;
  }

  bool windowed() const {
    return windowed_;
  }

  void present() {
    detail::present(device(), windowed(), before_reset, after_reset);
  }

  void resize(const int width, const int height) {
    width_ = width;
    height_ = height;
    detail::reset(device(), windowed(), width, height, before_reset, after_reset);
  }

  void change_screen_mode(const bool windowed) {
    detail::reset(device(), windowed, width(), height(), before_reset, after_reset);
  }

  int width() const {
    return width_;
  }

  int height() const {
    return height_;
  }

  const device_handle &device() const {
    return device_;
  }

  before_reset_signal before_reset;
  after_reset_signal after_reset;

 private:
  singleton() : windowed_(true),
                width_(640),
                height_(480),
                base_(create_base()),
                device_(create_device(window::detail::window(), base_, windowed_)) {
    init_device(device_);
  }

  bool windowed_;
  int width_;
  int height_;
  const base_handle base_;
  const device_handle device_;
};

inline
const device_handle &device() {
  return singleton::instance().device();
}

inline
bool windowed() {
  return singleton::instance().windowed();
}

inline
int width() {
  return singleton::instance().width();
}

inline
int height() {
  return singleton::instance().height();
}

inline
before_reset_signal &before_reset() {
  return singleton::instance().before_reset;
}

inline
after_reset_signal &after_reset() {
  return singleton::instance().after_reset;
}

inline
void present() {
  singleton::instance().present();
}

inline
void resize(const int width, const int height) {
  singleton::instance().resize(width, height);
}

inline
void change_screen_mode(const bool windowed) {
  singleton::instance().change_screen_mode(windowed);
}
}}}
