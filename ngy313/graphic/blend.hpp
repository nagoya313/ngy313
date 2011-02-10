#pragma once
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/blend_tag.hpp>
#include <ngy313/graphic/drawable.hpp>

namespace ngy313 { namespace graphic {
template <typename Drawable, typename BlendPair>
struct blend_adaptor {
  typedef add_drawable_adaptor<Drawable, add_blend_pair<Drawable, BlendPair>> type;
};

template <typename Drawable, typename Blend>
blend_adaptor<Drawable, typename Blend::pair_type> make_blend(const Drawable &drawable, const Blend &) {
  return blend_adaptor<Drawable, typename Blend::pair_type>(drawable);
}

template <typename SrcBlendTag, typename DestBlendTag>
struct blend : public adaptor::base<blend> {
  typedef blend_pair<SrcBlendTag, DestBlendTag> pair_type;

  template <typename Drawable>
  typename blend_adaptor<Drawable, pair_type>::type operator ()(const Drawable &drawable) const {
    return blend_adaptor<Drawable, pair_type>::type(drawable);
  }
};

typedef blend<src_alpha_blend_tag, one_blend_tag> add_blend_t;
typedef blend<zero_blend_tag, inv_src_color_blend_tag> sub_blend_t;
typedef blend<zero_blend_tag, src_color_blend_tag> mul_blend_t;
typedef blend<dest_color_blend_tag, src_color_blend_tag> mul2_blend_t;
typedef blend<inv_dest_color_blend_tag, one_blend_tag> screen_blend_t;
typedef blend<inv_dest_color_blend_tag, inv_src_color_blend_tag> reverse_blend_t;

const add_blend_t add_blend = add_blend_t();
const sub_blend_t sub_blend = sub_blend_t();
const mul_blend_t mul_blend = mul_blend_t();
const mul2_blend_t mul2_blend = mul2_blend_t();
const screen_blend_t screen_blend = screen_blend_t();
const reverse_blend_t reverse_blend = reverse_blend_t();
}}