#pragma once
#include "blend_filter_adaptor.hpp"

namespace ngy313 { namespace detail {
template <typename Drawable>
struct add_blend_filter 
    : public blend_filter_adaptor<Drawable, src_alpha_blend_tag, one_blend_tag> {
  explicit add_blend_filter(const Drawable &drawable) 
      : blend_filter_adaptor(drawable) {}
};

const struct add_blend_t : public filtered_base<add_blend_filter> {
  template <typename Drawable>
  add_blend_filter<Drawable> operator ()(const Drawable &drawable) const {
    return add_blend_filter<Drawable>(drawable);
  }
} add_blend;

}}

namespace ngy313 {
using detail::add_blend;
}