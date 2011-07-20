#ifndef NGY313_DETAIL_GTKMM_MESSAGE_BOX_HPP_
#define NGY313_DETAIL_GTKMM_MESSAGE_BOX_HPP_

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <gtkmm.h>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
class gtkmm_message_box : boost::noncopyable {
 public:
  typedef Gtk::MessageType icon_type;
  typedef Gtk::ButtonsType button_type;
  typedef int result_type;

  static int run(const string_wrap &message,
                 const string_wrap &caption,
                 Gtk::ButtonsType botton,
                 Gtk::MessageType icon) {
    Gtk::MessageDialog diag(message.c_str(),
                            false, 
                            icon, 
                            botton);
    diag.set_title(caption.c_str());
    return diag.run();
  }

  template <typename Window>
  static int run(const Window &window,
                 const string_wrap &message,
                 const string_wrap &caption,
                 Gtk::ButtonsType botton,
                 Gtk::MessageType icon) {
    Gtk::MessageDialog diag(*window.handle(),
                            message.c_str(),
                            false, 
                            icon, 
                            botton);
    diag.set_title(caption.c_str());
    return diag.run();
  	return 0;
  }

  BOOST_STATIC_CONSTEXPR Gtk::MessageType kNoIcon
      = Gtk::MESSAGE_OTHER;
  BOOST_STATIC_CONSTEXPR Gtk::MessageType kIconStop
      = Gtk::MESSAGE_ERROR;
  BOOST_STATIC_CONSTEXPR Gtk::MessageType kIconInformation
      = Gtk::MESSAGE_INFO;
  BOOST_STATIC_CONSTEXPR Gtk::MessageType kIconExclamation
      = Gtk::MESSAGE_WARNING;
  BOOST_STATIC_CONSTEXPR Gtk::MessageType kIconQuestion
      = Gtk::MESSAGE_QUESTION;

  BOOST_STATIC_CONSTEXPR Gtk::ButtonsType kButtonOK
      = Gtk::BUTTONS_OK;
  BOOST_STATIC_CONSTEXPR Gtk::ButtonsType kButtonYesNo
      = Gtk::BUTTONS_YES_NO;

  BOOST_STATIC_CONSTEXPR int kOK = Gtk::RESPONSE_OK;
  BOOST_STATIC_CONSTEXPR int kYes = Gtk::RESPONSE_YES;
  BOOST_STATIC_CONSTEXPR int kNo = Gtk::RESPONSE_NO;
  
  gtkmm_message_box() = delete;
};
}}

#endif
