#pragma once
#include <boost/noncopyable.hpp>
#include "detail/multiplex_starting_check.hpp"

namespace ngy313 {
class multiplex_starting_check : private boost::noncopyable {
 public:
  explicit multiplex_starting_check(const string_piece &name) : mutex_(detail::create_mutex(name)),
                                                                multipex_starting_(detail::existed_mutex()) {}
  
  bool multiplex_starting() const {
    return multipex_starting_;
  }

 private:
  const detail::mutex_handle mutex_;
  const bool multipex_starting_;
};
}