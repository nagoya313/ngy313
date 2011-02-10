#pragma once
#include <ngy313/process/detail/process.hpp>

namespace ngy313 { namespace process {
inline
int run(const std::function<void ()> work) {
  return detail::run(work);
}

inline
void quit() {
  detail::post_quit_message(0);
}

// cronoが来たらミリ時間指定が変るかも
inline
void sleep(const std::uint32_t time) {
  detail::sleep(time);
}
}}
