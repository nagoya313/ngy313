#ifndef NGY313_PROCESS_SINGLETON_HPP_
#define NGY313_PROCESS_SINGLETON_HPP_
#include <cstdint>
#include <functional>
#include <boost/noncopyable.hpp>

namespace ngy313 { namespace process { namespace detail {
template <typename Process>
class singleton : private boost::noncopyable {
 public:
  static singleton &instance() {
    static singleton inst;
    return inst;
  }
  
  Process &process() {
    return process_;
  }
 
 private:
  singleton() : process_() {}
  
  Process process_;
};
}}}

#endif

