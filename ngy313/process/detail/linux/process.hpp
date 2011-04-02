#ifndef NGY313_PROCESS_DETAIL_LINUX_PROCESS_HPP_
#define NGY313_PROCESS_DERAIL_LINUX_PROCESS_HPP_
#include <cstdint>
#include <functional>
#include <memory>
#include <boost/noncopyable.hpp>
#include <gtkmm.h>
#include <ngy313/process/detail/linux/initializer.hpp>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace process { namespace detail {
class main_process : private boost::noncopyable {
 public:
  template <typename Pred>
  int run(const Pred pred) {
    window::detail::window().set_func(pred);
    initializer::instance().kit()->run(window::detail::window().window());
    return 0;
  }
  
  static void quit(const int /*end_code*/) {
    initializer::instance().kit()->quit();
  }
  
  // cronoÇ™óàÇΩÇÁÇ‡Ç§è≠ÇµçlÇ¶ÇÈ
  static void sleep(const std::uint32_t time) {
    Glib::usleep(time);
  }
};
}}}

#endif

