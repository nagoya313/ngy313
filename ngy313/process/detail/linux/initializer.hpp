#ifndef NGY313_PROCESS_DETAIL_LINUX_INITIALIZER_HPP_
#define NGY313_PROCESS_DETAIL_LINUX_INITIALIZER_HPP_
#include <memory>
#include <boost/noncopyable.hpp>

namespace ngy313 { namespace process { namespace detail {
class initializer : private boost::noncopyable {
 public:
  static initializer &instance() {
    static initializer inst;
    return inst;
  }
  
  std::unique_ptr<Gtk::Main> &kit() {
    return kit_;
  }
  
 private:
  initializer() : kit_() {
    char empty_str[] = "";
    char *nul[1] = {empty_str};
    char **tempc = {nul};
    int tempv = 1;
    kit_.reset(new Gtk::Main(tempv, tempc));
  }
  
  std::unique_ptr<Gtk::Main> kit_;
};
}}}

#endif

