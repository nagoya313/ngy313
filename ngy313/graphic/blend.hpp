#ifndef NGY313_GRAPHIC_BLEND_HPP_
#define NGY313_GRAPHIC_BLEND_HPP_
#include <cassert>
#include <boost/mpl/pair.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/blend_type.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/blend_type.hpp>
#endif
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/blend_tag.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/utility/pipe_operator.hpp>

namespace ngy313 { namespace graphic {
template <typename Drawable, typename BlendPair>
struct blend_adaptor {
  typedef add_drawable_adaptor<Drawable, boost::mpl::pair<detail::blend_pair_key, BlendPair>> type;
};

template <typename Drawable, typename Blend>
blend_adaptor<Drawable, typename Blend::pair_type> make_blend(const Drawable &drawable, const Blend &) {
  return blend_adaptor<Drawable, typename Blend::pair_type>(drawable);
}

template <typename SrcBlendTag, typename DestBlendTag>
struct blend : public utility::pipe_operator::base<blend<SrcBlendTag, DestBlendTag>> {
  typedef blend_pair<SrcBlendTag, DestBlendTag> pair_type;

  template <typename Drawable>
  typename blend_adaptor<Drawable, pair_type>::type operator ()(const Drawable &drawable) const {
    return blend_adaptor<Drawable, pair_type>::type(drawable);
  }
};

typedef blend<src_alpha_blend_tag, inv_src_alpha_blend_tag> half_blend_t;
typedef blend<one_blend_tag, one_blend_tag> add_blend_t;
typedef blend<one_blend_tag, inv_src_alpha_blend_tag> half_add_blend_t;
typedef blend<zero_blend_tag, inv_src_color_blend_tag> sub_blend_t;
typedef blend<zero_blend_tag, src_color_blend_tag> mul_blend_t;
typedef blend<dest_color_blend_tag, src_color_blend_tag> mul2_blend_t;
typedef blend<inv_dest_color_blend_tag, one_blend_tag> screen_blend_t;
typedef blend<inv_dest_color_blend_tag, inv_src_color_blend_tag> reverse_blend_t;

const half_blend_t half_blend = half_blend_t();
const add_blend_t add_blend = add_blend_t();
const half_add_blend_t half_add_blend = half_add_blend_t();
const sub_blend_t sub_blend = sub_blend_t();
const mul_blend_t mul_blend = mul_blend_t();
const mul2_blend_t mul2_blend = mul2_blend_t();
const screen_blend_t screen_blend = screen_blend_t();
const reverse_blend_t reverse_blend = reverse_blend_t();
}}

#endif
