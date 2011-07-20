#ifndef NGY313_SINGLE_INSTANCE_CHECKER_HPP_
#define NGY313_SINGLE_INSTANCE_CHECKER_HPP_

#include <boost/noncopyable.hpp>
#include <ngy313/string_wrap.hpp>

#if defined(_WIN32)
#include <ngy313/detail/win32_single_instance_checker.hpp>
#elif defined(__linux__)
#include <ngy313/detail/fcntl_single_instance_checker.hpp>
#endif

namespace ngy313 {
template <typename Checker>
class basic_single_instance_checker : boost::noncopyable {
 public:
  explicit basic_single_instance_checker(const string_wrap &key)
    : checker_(key) {}

  bool another_running() const {
    return checker_.another_running();
  }

 private:
  Checker checker_;
};

#if defined(_WIN32)
typedef basic_single_instance_checker<
		 detail::win32_single_instance_checker> single_instance_checker;
#elif defined(__linux__)
typedef basic_single_instance_checker<
		 detail::fcntl_single_instance_checker> single_instance_checker;
#endif

}

#endif
