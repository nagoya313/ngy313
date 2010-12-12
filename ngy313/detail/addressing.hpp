#pragma once
#include <type_traits>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/contains.hpp>
#include <d3d9.h>
#include "drawable_adaptor.hpp"

namespace ngy313 { namespace detail {
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

typedef boost::mpl::vector<wrap_addressing_tag, 
                           mirror_addressing_tag,
                           clamp_addressing_tag> addressing_tag_list;

template <typename AddressingPair>
struct addressing_type {
  typedef AddressingPair addressing_pair_type;
};

template <typename U, typename V>
struct addressing_pair {
  static_assert(boost::mpl::contains<addressing_tag_list, U>::value, "");
  static_assert(boost::mpl::contains<addressing_tag_list, V>::value, "");
  typedef U u_type;
  typedef V v_type;
};

typedef addressing_pair<wrap_addressing_tag, wrap_addressing_tag> default_addressing;

template <typename Drawable, typename AddressingU, typename AddressingV>
struct addressing_adaptor_base
    : public vertex_adaptor<Drawable>,
      public addressing_type<addressing_pair<AddressingU, AddressingV>> {
  explicit addressing_adaptor_base(const Drawable &drawable) : all_vertex_adaptor(drawable) {}
};

template <typename AddressingU, typename AddressingV>
struct addressing_adaptor {
  template <typename Signature>
  struct result {
    typedef addressing_adaptor_base<typename copy_argument<Signature>::type, AddressingU, AddressingV> type;
  };

  template <typename Drawable>
  addressing_adaptor_base<Drawable, AddressingU, AddressingV> operator ()(const Drawable &drawable) const {
    return addressing_adaptor_base<Drawable, AddressingU, AddressingV>(drawable);
  }
};
}}