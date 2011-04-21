#ifndef NGY313_UTILITY_NONSUBSTIUTIABLE_HPP_
#define NGY313_UTILITY_NONSUBSTIUTIABLE_HPP_

namespace ngy313 { namespace utility { namespace nonsubstitutiable_ {
class nonsubstitutiable {
 protected:
  nonsubstitutiable() {}
  ~nonsubstitutiable() {}

 private:
  nonsubstitutiable &operator =(const nonsubstitutiable &rhs);
  nonsubstitutiable &operator =(nonsubstitutiable &&rhs);
};
}}}

namespace ngy313 { namespace utility {
using nonsubstitutiable_::nonsubstitutiable;
}}

#endif
