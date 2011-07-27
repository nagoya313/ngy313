#ifndef NGY313_DETAIL_MAIN_SINGLETON_HPP_
#define NGY313_DETAIL_MAIN_SINGLETON_HPP_

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>

#if defined(_MSC_VER)
#include <boost/thread.hpp>
#elif defined(__GNUC__)
#include <thread>
#endif

namespace ngy313 { namespace detail {
template <typename Main, typename Window, typename Graphic, typename Sound>
class basic_main_singleton : boost::noncopyable {
 public:
  static basic_main_singleton &instance() {
    static basic_main_singleton instance;
    return instance;
  }
  
  boost::optional<Main> &main_optional() {
    return main_;
  }

  Main &main() {
#if defined(_MSC_VER)
    static boost::once_flag flag = BOOST_ONCE_INIT;
    boost::call_once(flag, [this] {main_ = boost::in_place();});
#elif defined(__GNUC__)
    static std::once_flag flag;
    std::call_once(flag, [this] {main_ = boost::in_place();});
#endif
    assert(main_);
    return *main_;
  }

  boost::optional<Window> &window_optional() {
    return window_;
  }

  Window &window() {
#if defined(_MSC_VER)
    static boost::once_flag flag = BOOST_ONCE_INIT;
  	boost::call_once(flag, [this] {window_ = boost::in_place();});
#elif defined(__GNUC__)
    static std::once_flag flag;
    std::call_once(flag, [this] {window_ = boost::in_place();});
#endif
	assert(window_);
    return *window_optional();
  }
  
  boost::optional<Graphic> &graphic_optional() {
    return graphic_;
  }

  Graphic &graphic() {
#if defined(_MSC_VER)
  	static boost::once_flag flag = BOOST_ONCE_INIT;
  	boost::call_once(flag, [this] {graphic_ = boost::in_place(this->window());});
#elif defined(__GNUC__)
  	static std::once_flag flag;
  	std::call_once(flag, [this] {graphic_ = boost::in_place(this->window());});
#endif
    assert(graphic_);
    return *graphic_;
  }
  
  boost::optional<Sound> &sound_optional() {
    return sound_;
  }

  Sound &sound() {
#if defined(_MSC_VER)
  	static boost::once_flag flag = BOOST_ONCE_INIT;
  	boost::call_once(flag, [this] {sound_ = boost::in_place();});
#elif defined(__GNUC__)
  	static std::once_flag flag;
  	std::call_once(flag, [this] {sound_ = boost::in_place();});
#endif
    assert(sound_);
    return *sound_;
  }

 private:
  basic_main_singleton() : main_(), window_(), graphic_(), sound_() {}

  boost::optional<Main> main_;
  boost::optional<Window> window_;
  boost::optional<Graphic> graphic_;
  boost::optional<Sound> sound_;
};
}}

#endif
