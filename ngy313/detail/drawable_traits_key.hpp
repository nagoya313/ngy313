#ifndef NGY313_DETAIL_DRAWABLE_TRAITS_KEY_HPP_
#define NGY313_DETAIL_DRAWABLE_TRAITS_KEY_HPP_

#include <type_traits>
#include <ngy313/fvf_traits.hpp>

namespace ngy313 { namespace detail {
struct drawable_key {};
struct size_key {};
struct count_key {};
struct fvf_key {};
struct primitive_key {};
struct fusion_key {};
struct blend_pair_key {};
struct addressing_tuple_key {};
struct texture_stage_tuple_key {};
struct texture_data_key {};
struct base_point_key {};

template <typename Drawable>
struct drawable_switch_element {
  typedef typename fvf_traits<
      typename boost::mpl::at<typename std::decay<Drawable>::type::list_type,
                              fvf_key>::type>::texture_type type;
};
}}

#endif
