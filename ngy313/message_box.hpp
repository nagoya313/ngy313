#ifndef NGY313_MESSAGE_BOX_HPP_
#define NGY313_MESSAGE_BOX_HPP_

#include <boost/config.hpp>
#include <ngy313/string_wrap.hpp>
#include <ngy313/detail/ngy313.hpp>
#include <ngy313/detail/message_box.hpp>

namespace ngy313 {
enum icon_code {
  kNoIcon = detail::message_box::kNoIcon,
  kIconStop = detail::message_box::kIconStop,
  kIconInformation = detail::message_box::kIconInformation,
  kIconExclamation = detail::message_box::kIconExclamation,
  kIconQuestion = detail::message_box::kIconQuestion
};

enum button_code {
  kButtonOK = detail::message_box::kButtonOK,
  kButtonYesNo = detail::message_box::kButtonYesNo
};

BOOST_CONSTEXPR int kOK = detail::message_box::kOK;
BOOST_CONSTEXPR int kYes = detail::message_box::kYes;
BOOST_CONSTEXPR int kNo = detail::message_box::kNo;

inline
int message_box(const string_wrap &message,
                const string_wrap &caption,
                const button_code button,
                const icon_code icon) {
	detail::main_singleton::instance();
  return detail::message_box::run(
             message, 
             caption, 
             detail::message_box::transform_button_type(button),
             detail::message_box::transform_icon_type(icon));
}
}

#endif
