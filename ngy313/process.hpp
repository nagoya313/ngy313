#pragma once
#include <functional>
#include <pstade/oven/any_range.hpp>
#include <pstade/oven/iteration.hpp>
#include <pstade/oven/taken_while.hpp>
#include "detail/process.hpp"

namespace ngy313 {
inline
pstade::oven::any_range<int, boost::forward_traversal_tag> process_message() {
  return pstade::oven::iteration(false, [](bool) {
    return detail::has_message();
  }) | pstade::oven::taken_while([](const bool x) -> bool {
    if (x) {
      const detail::message mes = detail::get_message();
      if (!mes) {
        return false;
      } else {
        detail::translate_and_dispatch_message(mes);
      }
    }
    return true;
  });
}

struct main_loop {
  explicit main_loop(const std::function<void ()> &func) : func_(func) {}

  void operator ()(int) const {
    func_();
  }

 private:
  const std::function<void ()> func_;
};

inline
void quit() {
  detail::post_quit_message(0);
}

inline
void sleep(const std::uint32_t time) {
  detail::sleep_process(time);
}
}
