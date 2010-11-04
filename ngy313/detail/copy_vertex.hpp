#pragma once
#include <pstade/oven/algorithm.hpp>

namespace ngy313 {
template <typename Drawable>
typename Drawable::vertex_array_type copy_vertex(const Drawable &drawable) {
  typename Drawable::vertex_array_type vertex;
  pstade::oven::copy(drawable.vertex(), vertex.begin());
  return vertex;
}
}