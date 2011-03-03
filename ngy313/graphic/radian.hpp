#pragma once
#include <boost/mpl/at.hpp>
#include <d3dx9math.h>
#include <ngy313/graphic/detail/key.hpp>

namespace ngy313 { namespace graphic {
template <typename Drawable, int Index>
struct vertex_radian {
  static const float value;
};

template <typename Drawable, int Index>
const float vertex_radian<Drawable, Index>::value = 
    D3DX_PI * 2.f * static_cast<float>(Index - 1) / static_cast<float>(boost::mpl::at<
                                                                          typename Drawable::list_type, 
                                                                          detail::count_key>::type::type::value - 2);

template <typename Drawable, int Index>
struct line_vertex_radian {
  static const float value;
};

template <typename Drawable, int Index>
const float line_vertex_radian<Drawable, Index>::value = 
    D3DX_PI * 2.f * static_cast<float>(Index) / static_cast<float>(boost::mpl::at<
                                                                      typename Drawable::list_type, 
                                                                      detail::count_key>::type::type::value - 1);
}}
