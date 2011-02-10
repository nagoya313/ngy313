#pragma once
// �悭�l�����疼�O�p�C�v�Ƃ��ɂ����ق����悩��������

namespace ngy313 { namespace adaptor {
template <typename Base, typename Adaptor>
auto operator |(const Base &base, const Adaptor &adapt) -> decltype(adapt(base)) {
  return adapt(base);
}

template <typename Base, typename Adaptor>
auto operator |(Base &base, const Adaptor &adapt) -> decltype(adapt(base)) {
  return adapt(base);
}

template <typename Adaptor>
struct base {};
}}
