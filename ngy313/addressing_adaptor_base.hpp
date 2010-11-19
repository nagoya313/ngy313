#pragma once
#include "detail/addressing_tag.hpp"
#include "drawable_adaptor_base.hpp"

namespace ngy313 { namespace detail {
template <typename Drawable, typename AddressingU, typename AddressingV>
struct addressing_adaptor_base
    : public all_vertex_adaptor<Drawable>,
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

namespace ngy313 {
using detail::addressing_adaptor;
}
