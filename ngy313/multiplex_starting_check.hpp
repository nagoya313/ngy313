#pragma once
#include <boost/noncopyable.hpp>
#include <boost/mpl/string.hpp>
#include "detail/multiplex_starting_check.hpp"

namespace ngy313 {
template <typename MPLString>
class multiplex_starting_check : private boost::noncopyable {
 public:
  multiplex_starting_check() : mutex_(detail::create_mutex(boost::mpl::c_str<MPLString>::value)),
                               multipex_starting_(detail::existed_mutex()) {}
  
  bool multiplex_starting() const {
    return multipex_starting_;
  }

 private:
  const detail::mutex_handle mutex_;
  const bool multipex_starting_;
};
}