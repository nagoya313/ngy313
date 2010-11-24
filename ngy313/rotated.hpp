#pragma once
#include <cmath>
#include "drawable_adaptor.hpp"

namespace ngy313 { namespace detail {
struct rotate_position : public argument_result {
  template <typename Drawable, typename BasePoint>
  rotate_position(const Drawable &drawable, const BasePoint &base_point, const float angle)
      : base_point_x_(base_point.x(drawable)),
        base_point_y_(base_point.y(drawable)),
        cos_(std::cos(angle)),
        sin_(std::sin(angle)) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    const float x = vertex_member_at<rhw_position_t>(vertex).x - base_point_x_;
    const float y = vertex_member_at<rhw_position_t>(vertex).y - base_point_y_;
    vertex_member_at<rhw_position_t>(vertex).x = x * cos_ - y * sin_ + base_point_x_;
    vertex_member_at<rhw_position_t>(vertex).y = x * sin_ + y * cos_ + base_point_y_;
    return vertex;
  }

 private:
  const float base_point_x_;
  const float base_point_y_;
  const float cos_;
  const float sin_;
};

template <typename Drawable>
struct rotated_adaptor : public all_vertex_adaptor<Drawable> {
  template <typename BasePoint>
  rotated_adaptor(const Drawable &drawable, const BasePoint &base_point, const float angle)
      : all_vertex_adaptor(drawable, pstade::oven::transformed(rotate_position(drawable, base_point, angle))) {}
};

template <typename BasePoint>
struct rotated_t : public adaptor_result<rotated_adaptor> {
  explicit rotated_t(const BasePoint base_point, const float angle) : base_point_(base_point), angle_(angle) {}

  template <typename Drawable>
  rotated_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return rotated_adaptor<Drawable>(drawable, base_point_, angle_);
  }

 private:
  const BasePoint base_point_;
  const float angle_;
};

template <typename BasePoint>
rotated_t<BasePoint> rotated(const BasePoint base_point, const float angle) {
  return rotated_t<BasePoint>(base_point, angle);
}
}}

namespace ngy313 {
using detail::rotated;
}