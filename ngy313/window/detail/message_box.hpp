#pragma once
#include <cstdint>
#include <exception>
#include <Windows.h>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/singleton.hpp>

namespace ngy313 { namespace window {
enum icon_code {
  kNoIcon = 0,
  kIconStop = MB_ICONSTOP
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
                 const std::uint32_t flag) {
  // ó¨êŒÇ…âòÇ∑Ç¨ÇÈÇÃÇ≈Ç»ÇÒÇ∆Ç©Ç∑ÇÈ
  try {
    return MessageBox(window().window(), message.c_str(), caption.c_str(), flag);
  } catch(const std::exception &) {
    return MessageBox(nullptr, message.c_str(), caption.c_str(), flag);
  }
}
}}}
