#ifndef NGY313_PROCESS_DETAIL_MULTIPLEX_STARTING_CHECK_HPP_
#define NGY313_PROCESS_DETAIL_MULTIPLEX_STARTING_CHECK_HPP_
#include <boost/noncopyable.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS)
#include <ngy313/process/detail/windows/check.hpp>
#elif defined(NGY313_LINUX)
#include <ngy313/process/detail/linux/check.hpp>
#endif

namespace ngy313 { namespace process { namespace detail {
template <typename Check>
class multiplex_starting_check : private boost::noncopyable {
 public:
  explicit multiplex_starting_check(const utility::string_piece &name) : check_(name) {}
  
  bool multiplex_starting() const {
    return check_.multiplex_starting();
  }

 private:
  const Check check_;
};
}}}

#endif
