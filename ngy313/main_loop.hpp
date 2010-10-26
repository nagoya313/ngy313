#pragma once
#include <functional>

namespace ngy313 {
struct main_loop {
  explicit main_loop(const std::function<void ()> &func) : func_(func) {}

  void operator ()(int) const {
    func_();
  }

 private:
  const std::function<void ()> func_;
};
}
