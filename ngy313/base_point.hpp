#pragma once
#include "shape_position.hpp"

namespace ngy313 {
struct base_point_set {
  base_point_set(const float x, const float y) : x_(x), y_(y) {}

  template <typename Drawable>
  float x(const Drawable &) const {
    return x_;
  }

  template <typename Drawable>
  float y(const Drawable &) const {
    return y_;
  }

 private:
  const float x_;
  const float y_;
};

struct base_point_set_at {
  explicit base_point_set_at(const std::size_t at) : at_(at) {}

  template <typename Drawable>
  float x(const Drawable &drawable) const {
    return ngy313::shape_position_at_x(drawable, at_);
  }

  template <typename Drawable>
  float y(const Drawable &drawable) const {
    return ngy313::shape_position_at_y(drawable, at_);
  }

 private:
  const std::size_t at_;
};

const struct base_point_set_center_t {
  template <typename Drawable>
  float x(const Drawable &drawable) const {
    return ngy313::shape_center_x(drawable);
  }

  template <typename Drawable>
  float y(const Drawable &drawable) const {
    return ngy313::shape_center_y(drawable);
  }
} base_point_set_center = {};
}