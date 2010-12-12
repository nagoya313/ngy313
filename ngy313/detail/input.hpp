#pragma once
#include <boost/signals2/signal.hpp>
#include <Windows.h>
#include "singleton.hpp"

namespace ngy313 { namespace detail {
class input_singleton : public singleton<input_singleton> {
 public:
  boost::signals2::signal<void ()> input_callback;

 private:
  input_singleton() {}

  friend singleton<input_singleton>;
};

inline
boost::signals2::signal<void ()> &input_callback() {
  return input_singleton::instance().input_callback;
}

inline
bool pressed(const int key) {
  return GetAsyncKeyState(key) < 0;
}
}}