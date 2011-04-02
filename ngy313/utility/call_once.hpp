#ifndef NGY313_UTILITY_CALL_ONCE_HPP_
#define NGY313_UTILITY_CALL_ONCE_HPP_

namespace ngy313 { namespace utility {
// ëΩï™Ç±ÇÍÇ≈ëÂè‰ïvÇæÇ∆évÇ§
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

#endif

