#pragma once
#include <boost/mpl/if.hpp>
#include <d3dx9math.h>

namespace ngy313 { namespace detail {
template <typename Drawable, int Index>
struct vertex_radian {
  static const float value;
};

template <typename Drawable, int Index>
const float vertex_radian<Drawable, Index>::value = 
    D3DX_PI * 2.f * static_cast<float>(Index - 1) / static_cast<float>(typename Drawable::size_type::value - 2);

template <typename Drawable, int Index>
struct line_vertex_radian {
  static const float value;
};

template <typename Drawable, int Index>
const float line_vertex_radian<Drawable, Index>::value = 
    D3DX_PI * 2.f * static_cast<float>(Index) / static_cast<float>(typename Drawable::size_type::value - 1);

struct point2 {
  point2(const float ix, const float iy) : x(ix), y(iy) {}
  float x;
  float y;
};

struct point3 {
  point3(const float ix, const float iy, const float iz) : x(ix), y(iy), z(iz) {}
  float x;
  float y;
  float z;
};

const struct add_position_x_t {
  template <typename Vertex>
  float operator ()(const float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<rhw_position_t>(vertex).x;
  }
} add_position_x = {};

const struct add_position_y_t {
  template <typename Vertex>
  float operator ()(const float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<rhw_position_t>(vertex).y;
  }
} add_position_y = {};

const struct add_position_z_t {
  template <typename Vertex>
  float operator ()(const float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<rhw_position_t>(vertex).z;
  }
} add_position_z = {};

inline
float extend_position_impl(const float pos, const float base, const float extend) {
  return (pos - base) * extend + base;
}
}}