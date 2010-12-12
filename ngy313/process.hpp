#pragma once
#include <functional>
#include "detail/process.hpp"

namespace ngy313 {
inline
int run(const std::function<void ()> work) {
  return detail::run(work);
}

inline
void quit() {
  detail::post_quit_message(0);
}

inline
void sleep(const std::uint32_t time) {
  detail::sleep(time);
}
}
