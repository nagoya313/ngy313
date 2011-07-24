#ifndef NGY313_DETAIL_MAIN_SINGLETON_HPP_
#define NGY313_DETAIL_MAIN_SINGLETON_HPP_

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/config.hpp>

#if defined(_MSC_VER)
#define NGY313_USE_BOOST_THREAD
#endif

#if defined(NGY313_USE_BOOST_THREAD)
#include <boost/thread.hpp>
#else
#include <thread>
#endif

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
    main_init();
    return *main_;
  }

  boost::optional<Window> &window_optional() {
    main_init();
#if defined(NGY313_USE_BOOST_THREAD)
 	  static boost::once_flag flag = BOOST_ONCE_INIT;
  	boost::call_once(flag, [this] {this->window_init();});
#else
    static std::once_flag flag;
    std::call_once(flag, [this] {this->window_init();});
#endif
    return window_;
  }

  Window &window() {
    return *window_optional();
  }

  Graphic &graphic() {
#if defined(NGY313_USE_BOOST_THREAD)
  	static boost::once_flag flag = BOOST_ONCE_INIT;
  	boost::call_once(flag, [this] {this->graphic_init();});
#else
  	static std::once_flag flag;
  	std::call_once(flag, [this] {this->graphic_init();});
#endif
    return *graphic_;
  }

  Sound &sound() {
#if defined(NGY313_USE_BOOST_THREAD)
  	static boost::once_flag flag = BOOST_ONCE_INIT;
  	boost::call_once(flag, [this] {this->sound_init();});
#else
  	static std::once_flag flag;
  	std::call_once(flag, [this] {this->sound_init();});
#endif
    return *sound_;
  }

 private:
  basic_main_singleton() : main_(), 
                           window_(),
                           graphic_(),
                           sound_() {}

  static Window init_window() {
    Window window;
    window.move(0, 0);
    window.resize(640, 480);
    window.set_caption("");
    return window;
  }

  void main_init() {
#if defined(NGY313_USE_BOOST_THREAD)
    static boost::once_flag flag = BOOST_ONCE_INIT;
    boost::call_once(flag, [this] {main_ = boost::in_place();});
#else
    static std::once_flag flag;
    std::call_once(flag, [this] {main_ = boost::in_place();});
#endif
  }

  void window_init() {
  	window_ = boost::in_place();
  }

  void graphic_init() {
    graphic_ = boost::in_place(window());
  }

  void sound_init() {
   sound_ = boost::in_place();
  }

  boost::optional<Main> main_;
  boost::optional<Window> window_;
  boost::optional<Graphic> graphic_;
  boost::optional<Sound> sound_;
};
}}

#endif
