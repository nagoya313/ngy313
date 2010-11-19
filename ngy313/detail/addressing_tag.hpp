#pragma once
#include <d3d9.h>

namespace ngy313 {
template <typename AddressingPair>
struct addressing_type {
  typedef AddressingPair addressing_pair_type;
};

template <typename U, typename V>
struct addressing_pair {
  typedef U u_type;
  typedef V v_type;
};

struct addressing_tag {
  typedef D3DTEXTUREADDRESS value_type;
};

struct wrap_addressing_tag : public addressing_tag {
  static const value_type value = D3DTADDRESS_WRAP;
};

struct mirror_addressing_tag : public addressing_tag {
  static const value_type value = D3DTADDRESS_MIRROR;
};

struct clamp_addressing_tag : public addressing_tag {
  static const value_type value = D3DTADDRESS_CLAMP;
};

typedef addressing_pair<wrap_addressing_tag, wrap_addressing_tag> default_addressing;
}
