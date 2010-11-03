#pragma once
#include <boost/noncopyable.hpp>

namespace ngy313 { namespace detail {
template <typename T>
class singleton : private boost::noncopyable {
 public:
  static T &instance() {
    static T t;
    return t;
  }
};
}}