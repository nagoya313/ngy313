#pragma once
#include "detail/blend_tag.hpp"
#include "drawable_adaptor_base.hpp"

namespace ngy313 { namespace detail {
template <typename Drawable, typename SrcBlendTag, typename DestBlendTag>
struct blend_adaptor_base
    : public all_vertex_adaptor<Drawable, insert_blend_pair<Drawable, blend_pair<SrcBlendTag, DestBlendTag>>> {
  explicit blend_adaptor_base(const Drawable &drawable) : all_vertex_adaptor(drawable) {}
};
}}

namespace ngy313 {
template <typename SrcBlendTag, typename DestBlendTag>
struct blend_adaptor {
  template <typename Signature>
  struct result {
    typedef detail::blend_adaptor_base<typename detail::copy_argument<Signature>::type, SrcBlendTag, DestBlendTag> type;
  };

  template <typename Drawable>
  detail::blend_adaptor_base<Drawable, SrcBlendTag, DestBlendTag> operator ()(const Drawable &drawable) const {
    return detail::blend_adaptor_base<Drawable, SrcBlendTag, DestBlendTag>(drawable);
  }
};
}