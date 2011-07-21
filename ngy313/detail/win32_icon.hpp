#ifndef NGY313_DETAIL_WIN32_ICON_HPP_
#define NGY313_DETAIL_WIN32_ICON_HPP_

#include <system_error>
#include <boost/noncopyable.hpp>
#include <Windows.h>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
class win32_icon : boost::noncopyable {
 public:
  typedef HICON handle_type;

  explicit win32_icon(const string_wrap &file_name) 
      : icon_(reinterpret_cast<HICON>(
                  LoadImage(nullptr, 
                  file_name.c_str(),
                  IMAGE_ICON, 
                  32,
                  32,
                  LR_DEFAULTSIZE | LR_SHARED | LR_LOADFROMFILE))) {
    if (!icon_) {
      throw std::system_error(std::error_code(GetLastError(), 
                                              std::system_category()),
                              "アイコンの読み込みに失敗しました。¥n詳細");
    }
  }
      
  HICON handle() const {
    return icon_;
  }
  
 private:
  HICON icon_;
};
}}

#endif
