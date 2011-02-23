#pragma once
#include <type_traits>
#include <ngy313/utility/declval.hpp>
// �悭�l�����疼�O�p�C�v�Ƃ��ɂ����ق����悩��������

namespace ngy313 { namespace adaptor {
template <typename Base, typename Adaptor>
decltype(utility::declval<Adaptor>()(utility::declval<Base>())) operator |(Base &&base, Adaptor &&adapt) {
  return std::forward<Adaptor>(adapt)(std::forward<Base>(base));
}

template <typename Adaptor>
struct base {};
}}
