#ifndef NGY313_SINGLE_INSTANCE_CHECKER_HPP_
#define NGY313_SINGLE_INSTANCE_CHECKER_HPP_

#include <boost/noncopyable.hpp>
#include <ngy313/platform.hpp>
#include <ngy313/string_piece.hpp>

#if defined(NGY313_USE_WIN32)
#include <ngy313/detail/win32_single_instance_checker.hpp>
#elif defined(NGY313_USE_FCNTL)
#include <ngy313/detail/fcntl_single_instance_checker.hpp>
#endif

namespace ngy313 {
template <typename Checker>
class basic_single_instance_checker : boost::noncopyable {
 public:
  explicit basic_single_instance_checker(const string_piece &key)
    : checker_(key) {}

  bool another_running() const {
    return checker_.another_running();
  }

 private:
  const Checker checker_;
};

#if defined(NGY313_USE_WIN32)
typedef basic_single_instance_checker<detail::win32_single_instance_checker> single_instance_checker;
#elif defined(NGY313_USE_FCNTL)
typedef basic_single_instance_checker<detail::fcntl_single_instance_checker> single_instance_checker;
#endif

}

#endif
