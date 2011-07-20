#ifndef NGY313_DETAIL_MAIN_SINGLETON_HPP_
#define NGY313_DETAIL_MAIN_SINGLETON_HPP_

#include <boost/noncopyable.hpp>

namespace ngy313 { namespace detail {
template <typename Main,
          typename Window,
          typename Graphic,
          typename Sound>
class basic_main_singleton : boost::noncopyable {
 public:
  static basic_main_singleton &instance() {
    static basic_main_singleton instance;
    return instance;
  }

  Main &main() {
    return main_;
  }

  Window &window() {
    return window_;
  }

  Graphic &graphic() {
    return graphic_;
  }

  Sound &sound() {
    return sound_;
  }

 private:
  basic_main_singleton() : main_(), 
                           window_(),
                           graphic_(window_) {}

  static Window init_window() {
    Window window;
    window.move(0, 0);
    window.resize(640, 480);
    window.set_caption("");
    return window;
  }

  Main main_;
  Window window_;
  Graphic graphic_;
  Sound sound_;
};
}}

#endif
