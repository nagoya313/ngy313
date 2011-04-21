#ifndef NGY313_WINDOW_DETAIL_WINDOWS_MESSAGE_BOX_HPP_
#define NGY313_WINDOW_DETAIL_WINDOWS_MESSAGE_BOX_HPP_
#include <cstdint>
#include <Windows.h>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace window {
enum icon_code {
  kNoIcon = 0,
  kIconStop = MB_ICONSTOP,
  kIconInformation = MB_ICONINFORMATION,
  kIconExclamation = MB_ICONEXCLAMATION,
  kIconQuestion = MB_ICONQUESTION
};

enum botton_code {
  kButtonOk = MB_OK,
  kButtonYesNo = MB_YESNO
};

const int kOk = IDOK;
const int kYes = IDYES;
const int kNo = IDNO;
}}

namespace ngy313 { namespace window { namespace detail {
inline
int message_box(const utility::string_piece &message, 
                const utility::string_piece &caption,
                const botton_code botton,
                const icon_code icon) {
  // Ç±ÇÍÇ≈Ç¢Ç¢Ç©ÇÕåãç\âˆÇµÇ¢Ç∆Ç±ÇÎ
  if (IsWindowVisible(window().window())) {
    return MessageBoxA(window().window(), message.c_str(), caption.c_str(), botton | icon);
  } else {
    return MessageBoxA(nullptr, message.c_str(), caption.c_str(), botton | icon);
  }
}
}}}

#endif
