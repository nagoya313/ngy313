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

// crono��������~�����Ԏw�肪�ς邩��
inline
void sleep(const std::uint32_t time) {
  detail::sleep(time);
}
}}
