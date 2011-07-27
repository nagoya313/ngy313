#ifndef NGY313_BLEND_HPP_
#define NGY313_BLEND_HPP_

#include <boost/config.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/vector.hpp>
#include <ngy313/pipe_operator.hpp>

namespace ngy313 {
template <typename Drawable, typename BlendPair>
struct blend_adaptor {
  typedef add_drawable_adaptor<boost::mpl::pair<detail::blend_pair_key,
                                                BlendPair>,
                               Drawable> type;
};

template <typename Src, typename Dest>
struct blend_pair {
  typedef Src src_type;
  typedef Dest dest_type;

 private:
  typedef boost::mpl::vector<one_blend_tag,
                             src_alpha_blend_tag,
                             inv_src_alpha_blend_tag,
                             zero_blend_tag,
                             src_color_blend_tag,
                             inv_src_color_blend_tag,
                             dest_color_blend_tag, 
                             inv_dest_color_blend_tag> blend_tag_list;

  static_assert(boost::mpl::contains<blend_tag_list, Src>::value,
                "Blend_tag of src is illegal.");
  static_assert(boost::mpl::contains<blend_tag_list, Dest>::value, 
                "Blend_tag of dest is illegal.");
};

template <typename Drawable, typename Blend>
blend_adaptor<Drawable, typename Blend::pair_type> make_blend(const Drawable &drawable,
                                                              const Blend &) {
  return blend_adaptor<Drawable, typename Blend::pair_type>(drawable);
}

template <typename SrcBlendTag, typename DestBlendTag>
struct blend : pipe_operator::base<blend<SrcBlendTag, DestBlendTag>> {
  typedef blend_pair<SrcBlendTag, DestBlendTag> pair_type;

  template <typename Drawable>
  typename blend_adaptor<Drawable, pair_type>::type 
      operator ()(const Drawable &drawable) const {
    return typename blend_adaptor<Drawable, pair_type>::type(drawable);
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

BOOST_CONSTEXPR_OR_CONST half_blend_t half_blend = half_blend_t();
BOOST_CONSTEXPR_OR_CONST add_blend_t add_blend = add_blend_t();
BOOST_CONSTEXPR_OR_CONST half_add_blend_t half_add_blend = half_add_blend_t();
BOOST_CONSTEXPR_OR_CONST sub_blend_t sub_blend = sub_blend_t();
BOOST_CONSTEXPR_OR_CONST mul_blend_t mul_blend = mul_blend_t();
BOOST_CONSTEXPR_OR_CONST mul2_blend_t mul2_blend = mul2_blend_t();
BOOST_CONSTEXPR_OR_CONST screen_blend_t screen_blend = screen_blend_t();
BOOST_CONSTEXPR_OR_CONST reverse_blend_t reverse_blend = reverse_blend_t();
}

#endif
