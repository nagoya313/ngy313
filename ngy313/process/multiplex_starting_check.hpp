#pragma once
#include <boost/noncopyable.hpp>
#include <ngy313/process/detail/mutex.hpp>

namespace ngy313 { namespace process {
class multiplex_starting_check : private boost::noncopyable {
 public:
  explicit multiplex_starting_check(const utility::string_piece &name) : mutex_(detail::create_mutex(name)),
                                                                         multipex_starting_(detail::existed_mutex()) {}
  
  bool multiplex_starting() const {
    return multipex_starting_;
  }

 private:
  const detail::mutex_handle mutex_;
  const bool multipex_starting_;
};
}}
