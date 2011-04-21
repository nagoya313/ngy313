#ifndef NGY313_WINDOW_DETAIL_LINUX_MESSAGE_BOX_HPP_
#define NGY313_WINDOW_DETAIL_LINUX_MESSAGE_BOX_HPP_
#include <cstdint>
#include <gtkmm.h>
#include <ngy313/utility/string_piece.hpp>
#include <ngy313/window/detail/window.hpp>

namespace ngy313 { namespace window {
enum icon_code {
  kNoIcon = Gtk::MESSAGE_OTHER,
  kIconStop = Gtk::MESSAGE_ERROR,
  kIconInformation = Gtk::MESSAGE_INFO,
  kIconExclamation = Gtk::MESSAGE_WARNING,
  kIconQuestion = Gtk::MESSAGE_QUESTION
};

enum botton_code {
  kButtonOk = Gtk::BUTTONS_OK,
  kButtonYesNo = Gtk::BUTTONS_YES_NO
};

const int kOk = Gtk::RESPONSE_OK;
const int kYes = Gtk::RESPONSE_YES;
const int kNo = Gtk::RESPONSE_NO;
}}

namespace ngy313 { namespace window { namespace detail {
inline
int message_box(const utility::string_piece &message, 
                const utility::string_piece &caption,
                const botton_code botton,
                const icon_code icon) {
  Gtk::MessageDialog diag(window().window(), message.c_str(), false, static_cast<Gtk::MessageType>(icon), static_cast<Gtk::ButtonsType>(botton));
  diag.set_title(caption.c_str());
  return diag.run();
}
}}}

#endif
