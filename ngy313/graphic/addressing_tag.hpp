#ifndef NGY313_GRAPHIC_ADDRESSING_TAG_HPP_
#define NGY313_GRAPHIC_ADDRESSING_TAG_HPP_
#include <cstddef>
#include <type_traits>
#include <boost/mpl/contains.hpp>
#include <boost/mpl/vector.hpp>
#include <ngy313/platform.hpp>
#if defined(NGY313_WINDOWS_VERSION)
#include <ngy313/graphic/detail/windows/addressing_type.hpp>
#elif defined(NGY313_LINUX_VERSION)
#include <ngy313/graphic/detail/linux/addressing_type.hpp>
#endif

namespace ngy313 { namespace graphic {
typedef std::integral_constant<detail::addressing_type, detail::kAddressWrap> wrap_addressing_tag;
typedef std::integral_constant<detail::addressing_type, detail::kAddressClamp> clamp_addressing_tag;

template <std::size_t Stage, typename U, typename V>
struct addressing_tuple {
  typedef std::integral_constant<std::size_t, Stage> stage_type;
  typedef U u_type;
  typedef V v_type;

 private:
  typedef boost::mpl::vector<wrap_addressing_tag, clamp_addressing_tag> addressing_tag_list;

  // エラーメッセージが日本語で書けないのはつらい
  static_assert(boost::mpl::contains<addressing_tag_list, U>::value, "");
  static_assert(boost::mpl::contains<addressing_tag_list, V>::value, "");
};

template <std::size_t Stage>
struct default_addressing {
  typedef addressing_tuple<Stage, clamp_addressing_tag, clamp_addressing_tag> type;
};
}}

#endif
