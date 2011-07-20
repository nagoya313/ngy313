#ifndef NGY313_DETAIL_MAIN_HPP_
#define NGY313_DETAIL_MAIN_HPP_

#include <cstdint>
#include <boost/noncopyable.hpp>

#if defined(_WIN32)
#include <ngy313/detail/win32_main.hpp>
#elif defined(__linux__)
#include <ngy313/detail/gtkmm_main.hpp>
#endif

namespace ngy313 { namespace detail {
template <typename Main>
class basic_main : private boost::noncopyable {
 public:
  basic_main() : main_() {}

  template <typename Pred>
  int run(const Pred &pred) {
    return main_.run(pred);
  }

  static void quit() {
    Main::quit();
  }

  static void sleep(const std::uint32_t time) {
    Main::sleep(time);
  }

 private:
  Main main_;
};

#if defined(_WIN32)
typedef basic_main<win32_main> main; 
#elif defined(__linux__)
typedef basic_main<gtkmm_main> main;
#endif
}}

#endif
