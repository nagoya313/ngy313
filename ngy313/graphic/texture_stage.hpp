#pragma once
#include <boost/mpl/pair.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/texture_stage_tag.hpp>
#include <ngy313/graphic/drawable.hpp>
#include <ngy313/utility/pipe_operator.hpp>

namespace ngy313 { namespace graphic {
template <typename Drawable, typename TextureStageTuple>
struct texture_stage_adaptor {
  typedef add_drawable_adaptor<Drawable, boost::mpl::pair<detail::texture_stage_tuple_key, TextureStageTuple>> type;
};

template <typename Drawable, typename Blend>
texture_stage_adaptor<Drawable, typename Blend::pair_type> make_blend(const Drawable &drawable, const Blend &) {
  return blend_adaptor<Drawable, typename Blend::pair_type>(drawable);
}

template <std::size_t Index, typename ColorTag, typename AlphaTag = void>
struct texture_stage : public utility::pipe_operator::base<texture_stage<Index, ColorTag, AlphaTag>> {
  typedef add_texture_stage_tuple<Index, ColorTag, AlphaTag> tuple_type;

  template <typename Drawable>
  typename texture_stage<Index, ColorTag, AlphaTag>::type operator ()(const Drawable &drawable) const {
    return texture_stage<Index, ColorTag, AlphaTag>::type(drawable);
  }
};
}}