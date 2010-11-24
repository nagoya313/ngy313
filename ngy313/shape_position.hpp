#pragma once
#include <pstade/oven/numeric.hpp>
#include <pstade/oven/at.hpp>
#include "detail/drawable_core_access.hpp"
#include "detail/fvf_traits.hpp"
#include "detail/shape_position.hpp"

namespace ngy313 {
template <typename Drawable>
float shape_position_at_x(const Drawable &drawable, const std::size_t at) {
  return vertex_member_at<rhw_position_t>(pstade::oven::at(detail::drawable_core_access::vertex_range(drawable), at)).x;
}

template <typename Drawable>
float shape_position_at_y(const Drawable &drawable, const std::size_t at) {
  return vertex_member_at<rhw_position_t>(pstade::oven::at(detail::drawable_core_access::vertex_range(drawable), at)).y;
}

template <typename Drawable>
float shape_position_at_z(const Drawable &drawable, const std::size_t at) {
  return vertex_member_at<rhw_position_t>(pstade::oven::at(detail::drawable_core_access::vertex_range(drawable), at)).z;
}

template <typename Drawable>
float shape_center_x(const Drawable &drawable) {
  return pstade::oven::accumulate(detail::drawable_core_access::vertex_range(drawable),
                                  0.f,
                                  detail::add_position_x) / static_cast<float>(typename Drawable::size_type::value);
}

template <typename Drawable>
float shape_center_y(const Drawable &drawable) {
  return pstade::oven::accumulate(detail::drawable_core_access::vertex_range(drawable),
                                  0.f,
                                  detail::add_position_y) / static_cast<float>(typename Drawable::size_type::value);
}

template <typename Drawable>
float shape_center_z(const Drawable &drawable) {
  return pstade::oven::accumulate(detail::drawable_core_access::vertex_range(drawable),
                                  0.f,
                                  detail::add_position_z) / static_cast<float>(typename Drawable::size_type::value);
}
}