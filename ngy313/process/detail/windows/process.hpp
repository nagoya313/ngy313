#ifndef NGY313_PROCESS_DETAIL_WINDOWS_PROCESS_HPP_
#define NGY313_PROCESS_DERAIL_WINDOWS_PROCESS_HPP_
#include <cstdint>
#include <functional>
#include <boost/noncopyable.hpp>
#include <Windows.h>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace process { namespace detail {
class main_process : private boost::noncopyable {
 public:
  template <typename Pred>
  static int run(const Pred pred) {
    window::detail::window().show();
    MSG mes;
    for (;;) {
      if (PeekMessage(&mes, nullptr, 0, 0, PM_NOREMOVE)) {
        const BOOL result = GetMessage(&mes, nullptr, 0, 0);
        if (!(result && ~result)) {
          break;
          } 
        TranslateMessage(&mes);
        DispatchMessage(&mes);
      } else {
        pred();
      }
    }
    return mes.wParam;
  }
  
  static void quit(const int end_code) {
    PostQuitMessage(end_code);
  }
  
  // cronoÇ™óàÇΩÇÁÇ‡Ç§è≠ÇµçlÇ¶ÇÈ
  static void sleep(const std::uint32_t time) {
    Sleep(time);
  }
};
}}}

#endif

