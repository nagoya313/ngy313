#pragma once

namespace ngy313 { namespace utility {
// ‘½•ª‚±‚ê‚Å‘åä•v‚¾‚Æv‚¤
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
