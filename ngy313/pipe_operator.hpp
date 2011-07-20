#ifndef NGY313_PIPE_OPERATOR_HPP_
#define NGY313_PIPE_OPERATOR_HPP_

#include <utility>

#if defined(_MSV_VER)
#include <boost/utility/declval.hpp>
#endif

namespace ngy313 { namespace pipe_operator {
#if defined(_MSC_VER)
template <typename Base, typename Adaptor>
decltype(boost::declval<Adaptor>()(boost::declval<Base>()))
    operator |(Base &&base, Adaptor &&adaptor) {
  return std::forward<Adaptor>(adaptor)(std::forward<Base>(base));
}
#else
template <typename Base, typename Adaptor>
decltype(std::declval<Adaptor>()(std::declval<Base>()))
    operator |(Base &&base, Adaptor &&adapter) {
  return std::forward<Adaptor>(adapter)(std::forward<Base>(base));
}
#endif

template <typename Adaptor>
struct base {};
}}

#endif
