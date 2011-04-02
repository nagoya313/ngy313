#ifndef NGY313_UTILITY_PIPE_OPERATOR_HPP_
#define NGY313_UTILITY_PIPE_OPERATOR_HPP_
#include <utility>
#include <ngy313/utility/declval.hpp>

namespace ngy313 { namespace utility { namespace pipe_operator {
template <typename Base, typename Adaptor>
decltype(declval<Adaptor>()(declval<Base>())) operator |(Base &&base, Adaptor &&adapt) {
  return std::forward<Adaptor>(adapt)(std::forward<Base>(base));
}

template <typename Adaptor>
struct base {};
}}}

#endif

