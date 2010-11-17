#pragma once
#include <cassert>
#include <pstade/oven/algorithm.hpp>
#include "com_fwd.hpp"

namespace ngy313 { namespace detail {
struct drawable_core_access {
  template <typename Drawable>
  static typename Drawable::vertex_range_type vertex_range(const Drawable &drawable) {
    return drawable.vertex_range();
  }

  template <typename Drawable>
  static typename Drawable::vertex_array_type copy_vertex(const Drawable &drawable) {
    Drawable::vertex_array_type vertex;
    pstade::oven::copy(drawable.vertex_range(), vertex.begin());
    return vertex;
  }

  template <typename Drawable>
  static const texture_handle &texture1(const Drawable &drawable) {
   return drawable.texture1_.get().texture;
  }

  template <typename Drawable>
  static const texture_handle &texture2(const Drawable &drawable) {
   return drawable.texture2_.get().texture;
  }
};
}}