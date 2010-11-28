#pragma once
#include <boost/mpl/if.hpp>
#include <pstade/oven/numeric.hpp>
#include <pstade/oven/at.hpp>
#include "detail/drawable_core_access.hpp"
#include "detail/fvf_traits.hpp"
#include "detail/shape_position.hpp"

namespace ngy313 {
template <typename Drawable>
struct vector_type {
  typedef boost::mpl::if_<std::is_base_of<rhw_position_t, typename Drawable::fvf_tag>,
                          vector2,
                          vector3>::type type;
};  

template <typename Drawable>
struct vertex_type {
  typedef boost::mpl::if_<std::is_base_of<rhw_position_t, typename Drawable::fvf_tag>,
                          rhw_position_t,
                          position_t>::type type;
};  
}

namespace ngy313 {
template <typename Drawable>
typename vector_type<Drawable>::type shape_position_at(const Drawable &drawable, const std::size_t at) {
  return vertex_member_at<typename vertex_type<Drawable>::type>(
             pstade::oven::at(detail::drawable_core_access::vertex_range(drawable), at)).pos; 
}

template <typename Drawable>
typename vector_type<Drawable>::type shape_center(const Drawable &drawable, const std::size_t at) {
  return pstade::oven::accumulate(detail::drawable_core_access::vertex_range(drawable),
                                  typename vector_type<Drawable>::type(),
                                  detail::add_position) / static_cast<float>(Drawable::size_type::value);; 
}
}