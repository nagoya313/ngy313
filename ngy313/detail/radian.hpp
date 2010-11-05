#pragma once
#include <d3dx9math.h>

namespace ngy313 { namespace detail {
template <typename Drawable, int Index>
struct vertex_radian {
  static const float value;
};

template <typename Drawable, int Index>
const float vertex_radian<Drawable, Index>::value = 
    D3DX_PI * 2.f * static_cast<float>(Index - 1) / 
        static_cast<float>(typename Drawable::size_type::value - 2);

template <typename Drawable, int Index>
struct line_vertex_radian {
  static const float value;
};

template <typename Drawable, int Index>
const float line_vertex_radian<Drawable, Index>::value = 
    D3DX_PI * 2.f * static_cast<float>(Index) / 
        static_cast<float>(typename Drawable::size_type::value - 1);
}}
