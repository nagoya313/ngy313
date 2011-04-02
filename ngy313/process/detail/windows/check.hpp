#ifndef NGY313_PROCESS_DETAIL_WINDOWS_CHECK_HPP_
#define NGY313_PROCESS_DETAIL_WINDOWS_CHECK_HPP_
#include <cassert>
#include <memory>
#include <stdexcept>
#include <string>
#include <boost/noncopyable.hpp>
#include <Windows.h>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace process { namespace detail {
struct mutex_delete {
  void operator ()(const HANDLE mutex) const {
    assert(mutex);
    CloseHandle(mutex);
  }
};

typedef std::unique_ptr<std::remove_pointer<HANDLE>::type, mutex_delete> mutex_handle;

inline 
mutex_handle create_mutex(const utility::string_piece &name) {
  const HANDLE mutex = CreateMutex(nullptr, FALSE, name.c_str());
  if (!mutex) {
    throw std::runtime_error("ミューテクスオブジェクトの作成に失敗しました");
  }
  return mutex_handle(mutex);
}

inline
bool existed_mutex() {
  return GetLastError() == ERROR_ALREADY_EXISTS;
}

class check : private boost::noncopyable {
 public:
  explicit check(const utility::string_piece &name) : mutex_(detail::create_mutex(name)),
                                                      multipex_starting_(detail::existed_mutex()) {}
  
  bool multiplex_starting() const {
    return multipex_starting_;
  }

 private:
  const detail::mutex_handle mutex_;
  const bool multipex_starting_;
};
}}}

#endif

