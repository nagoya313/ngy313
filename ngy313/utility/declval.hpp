#pragma once
#include <type_traits>

namespace ngy313 { namespace utility {
// �W���̂������炳�����Ɣj��
template <class T>
typename std::add_rvalue_reference<T>::type declval();
}}
