#ifndef NGY313_WINDOW_MESSAGE_BOX_HPP_
#define NGY313_WINDOW_MESSAGE_BOX_HPP_
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS)
#include <ngy313/window/detail/windows/message_box.hpp>
#elif defined(NGY313_LINUX)
#include <ngy313/window/detail/linux/message_box.hpp>
#endif

namespace ngy313 { namespace window {
inline
int message_box(const utility::string_piece &message, 
                const utility::string_piece &caption,
                const botton_code botton,
                const icon_code icon) {
  return detail::message_box(message, caption, botton, icon);
}
}}

#endif
