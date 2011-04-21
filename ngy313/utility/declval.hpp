#ifndef NGY313_UTILITY_DECLVAL_HPP_
#define NGY313_UTILITY_DECLVAL_HPP_
#include <type_traits>

namespace ngy313 { namespace utility {
// 標準のが来たらさっさと破棄
template <typename T>
typename std::add_rvalue_reference<T>::type declval();
}}

#endif
