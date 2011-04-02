#ifndef NGY313_WINDOW_DETAIL_SINGLETON_HPP_
#define NGY313_WINDOW_DETAIL_SINGLETON_HPP_
#include <cassert>
#include <boost/noncopyable.hpp>

namespace ngy313 { namespace window { namespace detail {
template <typename Window>
class singleton : private boost::noncopyable {
 public:
  static singleton &instance() {
    static singleton inst;
    return inst;
  }
  
  Window &window() {
    return window_;
  }

 private:
  singleton() : window_() {
    window_.resize(640, 480);
  }

  Window window_;
};
}}}

#endif

