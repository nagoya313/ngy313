#ifndef NGY313_DETAIL_MESSAGE_BOX_HPP_
#define NGY313_DETAIL_MESSAGE_BOX_HPP_

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <ngy313/string_wrap.hpp>

#if defined(_WIN32)
#include <ngy313/detail/win32_message_box.hpp>
#elif defined(__linux__)
#include <ngy313/detail/gtkmm_message_box.hpp>
#endif

namespace ngy313 { namespace detail {
template <typename DialogMessage>
class basic_message_box : private boost::noncopyable {
 public:
  typedef typename DialogMessage::icon_type icon_type;
  typedef typename DialogMessage::button_type button_type;
  typedef typename DialogMessage::result_type result_type;

  static result_type run(const string_wrap &message,
                         const string_wrap &caption,
                         button_type botton,
                         icon_type icon) {
    return DialogMessage::run(message, caption, botton, icon);
  }

  template <typename Window>
  static result_type run(const Window &window,
                         const string_wrap &message,
                         const string_wrap &caption,
                         button_type botton,
                         icon_type icon) {
    return DialogMessage::run(window, message, caption, botton, icon);
  }

  template <typename T>
  static icon_type transform_icon_type(T t) {
    return static_cast<icon_type>(t);
  }

  template <typename T>
  static button_type transform_button_type(T t) {
    return static_cast<button_type>(t);
  }

  BOOST_STATIC_CONSTEXPR icon_type kNoIcon = DialogMessage::kNoIcon;
  BOOST_STATIC_CONSTEXPR icon_type kIconStop = DialogMessage::kIconStop;
  BOOST_STATIC_CONSTEXPR icon_type kIconInformation
      = DialogMessage::kIconInformation;
  BOOST_STATIC_CONSTEXPR icon_type kIconExclamation
      = DialogMessage::kIconExclamation;
  BOOST_STATIC_CONSTEXPR icon_type kIconQuestion
      = DialogMessage::kIconQuestion;

  BOOST_STATIC_CONSTEXPR button_type kButtonOK = DialogMessage::kButtonOK;
  BOOST_STATIC_CONSTEXPR button_type kButtonYesNo
      = DialogMessage::kButtonYesNo;

  BOOST_STATIC_CONSTEXPR result_type kOK = DialogMessage::kOK;
  BOOST_STATIC_CONSTEXPR result_type kYes = DialogMessage::kYes;
  BOOST_STATIC_CONSTEXPR result_type kNo = DialogMessage::kNo;
  
 private:
  basic_message_box();
};

#if defined(_WIN32)
typedef basic_message_box<win32_message_box> message_box; 
#elif defined(__linux__)
typedef basic_message_box<gtkmm_message_box> message_box;
#endif

}}

#endif
