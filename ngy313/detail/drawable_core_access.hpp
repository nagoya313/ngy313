#pragma once
#include <pstade/oven/algorithm.hpp>

namespace ngy313 { namespace detail {
struct drawable_core_access {
  template <typename Drawable>
  static typename Drawable::vertex_range_type vertex_range(
      const Drawable &drawable) {
    return drawable.vertex_range();
  }

  template <typename Drawable>
  static typename Drawable::vertex_array_type copy_vertex(
      const Drawable &drawable) {
    Drawable::vertex_array_type vertex;
    pstade::oven::copy(drawable.vertex_range(), vertex.begin());
    return vertex;
  }
};
}}