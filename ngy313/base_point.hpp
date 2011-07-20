#ifndef NGY313_BASE_POINT_HPP_
#define NGY313_BASE_POINT_HPP_

#include <cstddef>
#include <ngy313/shape_position.hpp>
#include <ngy313/vector.hpp>

namespace ngy313 {
struct base_point_set {
  explicit base_point_set(const vector2 &pos) : pos_(pos) {}

  template <typename Drawable>
  float x(const Drawable &) const {
    return pos_.get_x();
  }

  template <typename Drawable>
  float y(const Drawable &) const {
    return pos_.get_y();
  }

  template <std::size_t Index, typename Drawable>
  float u(const Drawable &) const {
    return pos_.get_x();
  }

  template <std::size_t Index, typename Drawable>
  float v(const Drawable &) const {
    return pos_.get_y();
  }

 private:
  vector2 pos_;
};

struct base_point_set_at {
  explicit base_point_set_at(std::size_t at) : at_(at) {}

  template <typename Drawable>
  float x(const Drawable &drawable) const {
    return shape_position_x(drawable, at_);
  }

  template <typename Drawable>
  float y(const Drawable &drawable) const {
    return shape_position_y(drawable, at_);
  }

 private:
  std::size_t at_;
};

const struct base_point_set_center_t {
  template <typename Drawable>
  float x(const Drawable &drawable) const {
    return shape_center_x(drawable);
  }

  template <typename Drawable>
  float y(const Drawable &drawable) const {
    return shape_center_y(drawable);
  }

} base_point_set_center = {};
}

#endif
