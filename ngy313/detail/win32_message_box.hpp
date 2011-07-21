#ifndef NGY313_DETAIL_WIN32_MESSAGE_BOX_HPP_
#define NGY313_DETAIL_WIN32_MESSAGE_BOX_HPP_

#include <boost/config.hpp>
#include <boost/noncopyable.hpp>
#include <Windows.h>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
class win32_message_box : boost::noncopyable {
 public:
  typedef DWORD icon_type;
  typedef DWORD button_type;
  typedef int result_type;

  static int run(const string_wrap &message, 
                 const string_wrap &caption,
                 DWORD botton,
                 DWORD icon) {
    return MessageBox(nullptr, 
                      message.c_str(),
                      caption.c_str(),
                      botton | icon);
  }

  template <typename Window>
  static int run(const Window &window,
                 const string_wrap &message, 
                 const string_wrap &caption,
                 DWORD botton,
                 DWORD icon) {
    return MessageBox(window.handle(),
                      message.c_str(),
                      caption.c_str(),
                      botton | icon);
  }

  BOOST_STATIC_CONSTEXPR DWORD kNoIcon = 0;
  BOOST_STATIC_CONSTEXPR DWORD kIconStop = MB_ICONSTOP;
  BOOST_STATIC_CONSTEXPR DWORD kIconInformation = MB_ICONINFORMATION;
  BOOST_STATIC_CONSTEXPR DWORD kIconExclamation = MB_ICONEXCLAMATION;
  BOOST_STATIC_CONSTEXPR DWORD kIconQuestion = MB_ICONQUESTION;

  BOOST_STATIC_CONSTEXPR DWORD kButtonOK = MB_OK;
  BOOST_STATIC_CONSTEXPR DWORD kButtonYesNo = MB_YESNO;

  BOOST_STATIC_CONSTEXPR int kOK = IDOK;
  BOOST_STATIC_CONSTEXPR int kYes = IDYES;
  BOOST_STATIC_CONSTEXPR int kNo = IDNO;
  
 private:
  win32_message_box();
};
}}

#endif
