#pragma once
#include <type_traits>
#include <boost/mpl/if.hpp>
#include "shape_position.hpp"

namespace ngy313 {
template <typename Vector>
struct base_point_set_t {
  static_assert(std::is_same<Vector, vector2>::value || std::is_same<Vector, vector3>::value, "");

  explicit base_point_set_t(const Vector &pos) : pos_(pos) {}

  template <typename Drawable>
  Vector pos(const Drawable &) const {
    return pos_;
  }

 private:
  const Vector pos_;
};

template <typename Vector>
base_point_set_t<Vector> base_point_set(const Vector &pos) {
  return base_point_set_t<Vector>(pos);
}

struct base_point_set_at {
  explicit base_point_set_at(const std::size_t at) : at_(at) {}

  template <typename Drawable>
  typename detail::vector_type<Drawable>::type pos(const Drawable &drawable) const {
    return shape_position_at(drawable, at_);
  }

 private:
  const std::size_t at_;
};

const struct base_point_set_center_t {
  template <typename Drawable>
  typename detail::vector_type<Drawable>::type pos(const Drawable &drawable) const {
    return shape_center(drawable);
  }
} base_point_set_center = {};
}