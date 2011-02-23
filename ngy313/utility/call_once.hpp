#pragma once

namespace ngy313 { namespace utility {
// 多分これで大丈夫だと思う
struct call_once {
  template <typename Pred>
  explicit call_once(const Pred &pred) {
    static const call_once_t once(pred);
  }

 private:
  struct call_once_t {
    template <typename Pred>
    explicit call_once_t(const Pred pred) {
      pred();
    }
  };
};
}}
