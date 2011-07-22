#ifndef NGY313_UV_REVERSED_HPP_
#define NGY313_UV_REVERSED_HPP_

#include <ngy313/uv_extended.hpp>
#include <ngy313/base_point.hpp>

namespace ngy313 {
template <std::size_t Index, typename Drawable>
uv_extended_adaptor::detail::adaptor<Drawable, Index>
    make_uv_reversed(const Drawable &drawable) {
  return uv_extended_adaptor::detail::adaptor<Drawable, Index>(
             drawable, 
             base_point_set_center,
             vector2(-1.f, 1.f));
}

template <std::size_t Index>
uv_extended_adaptor::uv_extended_t<Index, base_point_set_center_t> uv_reversed() {
  return uv_extended_adaptor::uv_extended_t<Index, base_point_set_center_t>(
             base_point_set_center,
             vector2(-1.f, 1.f));
}
}

#endif