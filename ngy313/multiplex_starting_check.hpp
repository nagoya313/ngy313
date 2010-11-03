#pragma once
#include <boost/noncopyable.hpp>
#include <boost/mpl/string.hpp>
#include "detail/window_fwd.hpp"

namespace ngy313 {
template <typename MPLString>
class multiplex_starting_check : private boost::noncopyable {
 public:
  multiplex_starting_check()
      : mutex_(CreateMutex(nullptr, FALSE, boost::mpl::c_str<MPLString>::value)),
        multipex_starting_(GetLastError() == ERROR_ALREADY_EXISTS) {}
  
  bool multiplex_starting() const {
    return multipex_starting_;
  }

 private:
  const detail::mutex_handle mutex_;
  const bool multipex_starting_;
};
}