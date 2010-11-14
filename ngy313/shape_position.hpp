#pragma once
#include <pstade/oven/numeric.hpp>
#include <pstade/oven/at.hpp>
#include "detail/drawable_core_access.hpp"
#include "fvf_traits.hpp"

namespace ngy313 { namespace detail {
template <typename Vertex>
float add_position_x(const float lhs, const Vertex &vertex) {
  return lhs + member_at<rhw_position_t>(vertex).x;
}

template <typename Vertex>
float add_position_y(const float lhs, const Vertex &vertex) {
  return lhs + member_at<rhw_position_t>(vertex).y;
}
}}

namespace ngy313 {
template <typename Drawable>
float shape_at_x(const Drawable &drawable, const std::size_t at) {
  return member_at<rhw_position_t>(
             pstade::oven::at(drawable_core_access::vertex_range(drawable),
                              at)).x;
}

template <typename Drawable>
float shape_at_y(const Drawable &drawable, const std::size_t at) {
  return member_at<rhw_position_t>(
             pstade::oven::at(drawable_core_access::vertex_range(drawable),
                              at)).y;
}

template <typename Drawable>
float shape_center_x(const Drawable &drawable) {
  return pstade::oven::accumulate(drawable_core_access::vertex_range(drawable),
                                  0.f,
                                  &detail::add_position_x) / 
             static_cast<float>(typename Drawable::size_type::value);
}

template <typename Drawable>
float shape_center_y(const Drawable &drawable) {
  return pstade::oven::accumulate(drawable_core_access::vertex_range(drawable),
                                  0.f,
                                  &detail::add_position_y) / 
             static_cast<float>(typename Drawable::size_type::value);
}
}