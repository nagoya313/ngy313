#pragma once
#include <exception>
#include <Windows.h>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/singleton.hpp>

namespace ngy313 { namespace window {
enum icon_code {
  kStop = MB_ICONSTOP
};
}}

namespace ngy313 { namespace window { namespace detail {
inline
void message_box(const utility::string_piece &message, 
                 const utility::string_piece &caption,
                 icon_code icon) {
  try {
    MessageBox(window(), message.c_str(), caption.c_str(), icon);
  } catch(const std::exception &) {
    MessageBox(nullptr, message.c_str(), caption.c_str(), icon);
  }
}
}}}
