#ifndef NGY313_PROCESS_PROCESS_HPP_
#define NGY313_PROCESS_PROCESS_HPP_
#include <ngy313/process/detail/process.hpp>

namespace ngy313 { namespace process {
inline
int run(const std::function<void ()> work) {
  return detail::process().run(work);
}

inline
void quit() {
  detail::process().quit(0);
}

// crono‚ª—ˆ‚½‚çƒ~ƒŠŽžŠÔŽw’è‚ª•Ï‚é‚©‚à
inline
void sleep(const std::uint32_t time) {
  detail::process().sleep(time);
}
}}

#endif
