#ifndef NGY313_DETAIL_FCNTL_SINGLE_INSTANCE_CHECKER_HPP_
#define NGY313_DETAIL_FCNTL_SINGLE_INSTANCE_CHECKER_HPP_

#include <cassert>
#include <stdexcept>
#include <boost/noncopyable.hpp>
#include <fcntl.h>
#include <ngy313/scoped_handle.hpp>
#include <ngy313/string_wrap.hpp>

namespace ngy313 { namespace detail {
class fcntl_single_instance_checker : boost::noncopyable {
	struct file_delete {
    constexpr file_delete() = default;

	  void operator ()(int handle) const {
	    assert(handle >= 0);
	    close(handle);
	  }

	  constexpr int null_value() const {
	  	return -1;
	  }

	  constexpr bool null_check(int handle) const {
	  	return handle < 0;
	  }
	};

 public:
  explicit fcntl_single_instance_checker(const string_wrap &name)
      : file_(open_file(name)),
        another_running_(check_multiplex_starting(file_)) {}
  
  bool another_running() const {
    return another_running_;
  }

 private:
  static bool check_multiplex_starting(
  		 const scoped_handle<int, file_delete> &file) {
    flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_pid = getpid();
    return !(~fcntl(file.get(), F_SETLK, &fl));
  }

  static scoped_handle<int, file_delete> open_file(const string_wrap &name) {
    const int id = open(name.c_str(),
                        O_WRONLY | O_CREAT,
                        S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
    if (id < 0) {
      throw std::runtime_error("ファイルを開くのに失敗しました");
    }
    return scoped_handle<int, file_delete>(id);
  }
  
  scoped_handle<int, file_delete> file_;
  bool another_running_;
};
}}

#endif
