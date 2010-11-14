#pragma once
#include "drawable_filter_adaptor.hpp"

namespace ngy313 { namespace detail {
template <typename Src, typename Dest>
struct blend_pair {
  typedef Src src_type;
  typedef Dest dest_type;
};

typedef blend_pair<src_alpha_blend_tag, inv_src_alpha_blend_tag> default_blend;

template <typename Drawable, typename SrcBlendTag, typename DestBlendTag>
struct blend_filter_adaptor
    : public all_vertex_drawable_filter_adaptor<Drawable> {
  explicit blend_filter_adaptor(const Drawable &drawable) 
      : all_vertex_drawable_filter_adaptor(drawable) {}
};
}}