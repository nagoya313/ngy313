#ifndef NGY313_REVERSED_HPP_
#define NGY313_REVERSED_HPP_

#include <ngy313/extended.hpp>
#include <ngy313/base_point.hpp>

namespace ngy313 {
template <typename Drawable>
extended_adaptor::detail::adaptor<Drawable> make_reversed(const Drawable &drawable) {
  return extended_adaptor::detail::adaptor<Drawable>(drawable, 
                                                     base_point_set_center,
                                                     vector2(-1.f, 1.f));
}

const auto reversed = extended(base_point_set_center, vector2(-1.f, 1.f));
}

#endif
