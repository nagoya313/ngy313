#pragma once

namespace ngy313 { namespace utility {
// ‚±‚ê‚à”÷–­‚¾‚©‚çÁ‚·‚©‚à
template <bool Comp, typename IntegralType, IntegralType Then, IntegralType Else>
struct if_cc {
  typedef IntegralType value_type;
  static const IntegralType value = Then;
};

template <typename IntegralType, IntegralType Then, IntegralType Else>
struct if_cc<false, IntegralType, Then, Else> {
  typedef IntegralType value_type;
  static const IntegralType value = Else;
};
}}
