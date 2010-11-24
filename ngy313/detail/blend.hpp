#pragma once
#include <boost/mpl/vector.hpp>
#include <boost/mpl/contains.hpp>
#include <d3d9.h>
#include "drawable_adaptor.hpp"

namespace ngy313 { namespace detail {
struct blend_tag {
  typedef D3DBLEND value_type;
};

struct one_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_ONE;
};

struct src_alpha_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_SRCALPHA;
};

struct inv_src_alpha_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_INVSRCALPHA;
};

struct dest_alpha_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_DESTALPHA;
};

struct inv_dest_alpha_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_INVDESTALPHA;
};

struct zero_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_ZERO;
};

struct src_color_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_SRCCOLOR;
};

struct inv_src_color_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_INVSRCCOLOR;
};

struct dest_color_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_DESTCOLOR;
};

struct inv_dest_color_blend_tag : public blend_tag {
  static const value_type value = D3DBLEND_INVDESTCOLOR;
};

typedef boost::mpl::vector<one_blend_tag,
                           src_alpha_blend_tag,
                           inv_src_alpha_blend_tag,
                           dest_alpha_blend_tag,
                           inv_dest_alpha_blend_tag,
                           zero_blend_tag,
                           src_color_blend_tag,
                           inv_src_color_blend_tag,
                           dest_color_blend_tag, 
                           inv_dest_color_blend_tag> blend_tag_list;

template <typename BlendPair>
struct blend_type {
  typedef BlendPair blend_pair_type;
};

template <typename Src, typename Dest>
struct blend_pair {
  static_assert(boost::mpl::contains<blend_tag_list, Src>::value, "");
  static_assert(boost::mpl::contains<blend_tag_list, Dest>::value, "");
  typedef Src src_type;
  typedef Dest dest_type;
};

typedef blend_pair<src_alpha_blend_tag, inv_src_alpha_blend_tag> default_blend;

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