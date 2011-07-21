#ifndef NGY313_DETAIL_WIN32_SINGLE_INSTANCE_CHECKER_HPP_
#define NGY313_DETAIL_WIN32_SINGLE_INSTANCE_CHECKER_HPP_

#include <cassert>
#include <memory>
#include <system_error>
#include <type_traits>
#include <boost/noncopyable.hpp>
#include <Windows.h>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
class win32_single_instance_checker : boost::noncopyable {
 public:
  explicit win32_single_instance_checker(const string_wrap &name)
      : mutex_(create_mutex(name)), another_running_(existed_mutex()) {}

  bool another_running() const {
    return another_running_;
  }

 private:
  struct mutex_delete {
    void operator ()(HANDLE mutex) const {
      assert(mutex);
      CloseHandle(mutex);
    }
  };

  typedef std::unique_ptr<std::remove_pointer<HANDLE>::type, 
                          mutex_delete> mutex_handle;
  static mutex_handle create_mutex(const string_wrap &name) {
    const HANDLE mutex(CreateMutex(nullptr, FALSE, name.c_str()));
    if (!mutex) {
      throw std::system_error(std::error_code(GetLastError(),
                                              std::system_category()),
                              "ミューテクスオブジェクトの作成に失敗しました");
    }
    return mutex_handle(mutex);
  }

  static bool existed_mutex() {
    return GetLastError() == ERROR_ALREADY_EXISTS;
  }

  mutex_handle mutex_;
  bool another_running_;
};
}}

#endif
