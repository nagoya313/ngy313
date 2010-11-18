#pragma once
#include "detail/blend_tag.hpp"
#include "drawable_adaptor_base.hpp"

namespace ngy313 { namespace detail {
template <typename Drawable, typename SrcBlendTag, typename DestBlendTag>
struct blend_adaptor_base
    : public all_vertex_adaptor<Drawable>,
      public blend_type<blend_pair<SrcBlendTag, DestBlendTag>> {
  explicit blend_adaptor_base(const Drawable &drawable) : all_vertex_adaptor(drawable) {}
};

template <typename SrcBlendTag, typename DestBlendTag>
struct blend_adaptor {
  template <typename Signature>
  struct result {
    typedef blend_adaptor_base<typename copy_argument<Signature>::type, SrcBlendTag, DestBlendTag> type;
  };

  template <typename Drawable>
  blend_adaptor_base<Drawable, SrcBlendTag, DestBlendTag> operator ()(const Drawable &drawable) const {
    return blend_adaptor_base<Drawable, SrcBlendTag, DestBlendTag>(drawable);
  }
};
}}

namespace ngy313 {
using detail::blend_adaptor;
}