#ifndef NGY313_UTILITY_NULLPTR_HPP_
#define NGY313_UTILITY_NULLPTR_HPP_

namespace ngy313 { namespace utility {
const class nullptr_t {
 public:
  template<class T>
  operator T*() const {
    return 0;
  }
 
  template<class C, class T>
  operator T C::*() const {
    return 0;
  }
  
 private:
  void operator &() const;
} nullptr = {};
}}

#define nullptr ngy313::utility::nullptr

#endif

