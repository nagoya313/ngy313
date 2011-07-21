#ifndef NGY313_DETAIL_WIN32_MAIN_HPP_
#define NGY313_DETAIL_WIN32_MAIN_HPP_

#include <cstdint>
#include <functional>
#include <system_error>
#include <Windows.h>
#include <ngy313/detail/com.hpp>

namespace ngy313 { namespace detail {
class win32_main : boost::noncopyable {
 public:
  win32_main() {
    regist_window_class();
  }

  template <typename Pred>
  static int run(Pred pred) {
    for (;;) {
      MSG mes;
      if (PeekMessage(&mes, nullptr, 0, 0, PM_NOREMOVE)) {
        const BOOL result = GetMessage(&mes, nullptr, 0, 0);
        if (!(result && ~result)) {
          return mes.wParam;
        } 
        TranslateMessage(&mes);
        DispatchMessage(&mes);
      } else {
        pred();
      }
    }
  }

  static void quit() {
    PostQuitMessage(0);
  }

  static void sleep(std::uint32_t time) {
    Sleep(time);
  }

 private:
  static void regist_window_class() {
    WNDCLASSEX temp;
    if (!GetClassInfoEx(GetModuleHandle(nullptr), "MAINWINDOW", &temp)) {
      const WNDCLASSEX window_class  = {
        sizeof(window_class),
        CS_HREDRAW | CS_VREDRAW,
        &DefWindowProc,
        0,
        0,
        GetModuleHandle(nullptr),
        reinterpret_cast<HICON>(LoadImage(nullptr,
                                          IDI_APPLICATION, 
                                          IMAGE_ICON, 
                                          32,
                                          32,
                                          LR_DEFAULTSIZE | LR_SHARED)),
        reinterpret_cast<HCURSOR>(LoadImage(nullptr,
                                            IDC_ARROW, 
                                            IMAGE_CURSOR, 
                                            0,
                                            0,
                                            LR_DEFAULTSIZE | LR_SHARED)),
        reinterpret_cast<HBRUSH>(GetStockObject(WHITE_BRUSH)),
        nullptr,
        "MAINWINDOW",
        nullptr
      };
      if (!RegisterClassEx(&window_class)) {
        throw std::system_error(std::error_code(GetLastError(),
                                                std::system_category()),
                                "ウィンドウクラスの登録に失敗しました");
      }
    }
  }

  const com_initializer com_init_;
};
}}

#endif
