#pragma once

namespace ngy313 { namespace utility {
// ��������ő��v���Ǝv��
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
