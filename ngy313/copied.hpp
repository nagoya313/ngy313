#pragma once
#include "detail/drawable_filter.hpp"

namespace ngy313 {
namespace detail {
const struct copied_t {
  template <typename Signature>
  struct result {  
    typedef typename copy_argument<Signature>::type::drawable_type type;
  };

  template <typename Drawable>
  typename Drawable::drawable_type operator ()(const Drawable &drawable) const {
    return typename Drawable::drawable_type(drawable);
  }
} copied = {};
}
using detail::copied;
}