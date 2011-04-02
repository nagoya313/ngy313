#ifndef NGY313_GRAPGIC_BLEND_TAG_HPP_
#define NGY313_GRAPHIC_BLEND_TAG_HPP_
#include <type_traits>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/vector.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/blend_type.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/blend_type.hpp>
#endif

namespace ngy313 { namespace graphic {
typedef std::integral_constant<detail::blend_type, detail::kBlendOne> one_blend_tag;
typedef std::integral_constant<detail::blend_type, detail::kBlendSrcAlpha> src_alpha_blend_tag;
typedef std::integral_constant<detail::blend_type, detail::kBlendInvSrcAlpha> inv_src_alpha_blend_tag;
typedef std::integral_constant<detail::blend_type, detail::kBlendDestAlpha> dest_alpha_blend_tag;
typedef std::integral_constant<detail::blend_type, detail::kBlendInvDestAlpha> inv_dest_alpha_blend_tag;
typedef std::integral_constant<detail::blend_type, detail::kBlendZero> zero_blend_tag;
typedef std::integral_constant<detail::blend_type, detail::kBlendSrcColor> src_color_blend_tag;
typedef std::integral_constant<detail::blend_type, detail::kBlendInvSrcColor> inv_src_color_blend_tag;
typedef std::integral_constant<detail::blend_type, detail::kBlendDestColor> dest_color_blend_tag;
typedef std::integral_constant<detail::blend_type, detail::kBlendInvDestColor> inv_dest_color_blend_tag;

template <typename Src, typename Dest>
struct blend_pair {
  typedef Src src_type;
  typedef Dest dest_type;

 private:
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

  // エラーメッセージが日本語で書けないのはつらい
  static_assert(boost::mpl::contains<blend_tag_list, Src>::value, "");
  static_assert(boost::mpl::contains<blend_tag_list, Dest>::value, "");
};

typedef blend_pair<src_alpha_blend_tag, inv_src_alpha_blend_tag> default_blend;
}}

#endif
