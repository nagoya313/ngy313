#pragma once
#include <type_traits>

namespace ngy313 { namespace utility {
// 標準のが来たらさっさと破棄
template <class T>
typename std::add_rvalue_reference<T>::type declval();
}}
