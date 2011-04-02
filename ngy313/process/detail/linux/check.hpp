#ifndef NGY313_PROCESS_DETAIL_LINUX_CHECK_HPP_
#define NGY313_PROCESS_DETAIL_LINUX_CHECK_HPP_
#include <stdexcept>
#include <string>
#include <boost/noncopyable.hpp>
#include <fcntl.h>
#include <ngy313/utility/string_piece.hpp>

namespace ngy313 { namespace process { namespace detail {
class file_handle {
 public:
  explicit file_handle(const int id) : id_(id) {
    if (id_ < 0) {
      throw std::runtime_error("ファイルを開くのに失敗しました");
    }
  }
  
  ~file_handle() {
    close(id_);
  }
  
  int get() const {
    return id_;
  }
  
 private:
  const int id_;
};
  
class check : private boost::noncopyable {
 public:
  explicit check(const utility::string_piece &name) 
      : file_(open(name.c_str(), O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)),
        multiplex_starting_(false) {
    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0;
    fl.l_pid = getpid();
    multiplex_starting_ = !(~fcntl(file_.get(), F_SETLK, &fl));
  }
  
  bool multiplex_starting() const {
    return multiplex_starting_;
  }

 private:
  const file_handle file_;
  bool multiplex_starting_;
};
}}}

#endif

