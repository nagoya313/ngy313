#pragma once
#include <cmath>
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/adaptor/adaptor.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/shape_position.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
struct transform_rotate {
  transform_rotate(const float base_point_x, const float base_point_y, const float angle) 
      : base_point_x_(base_point_x), base_point_y_(base_point_y), cos_(std::cos(angle)), sin_(std::sin(angle)) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    const float x = vertex_member_at<position>(vertex).x - base_point_x_;
    const float y = vertex_member_at<position>(vertex).y - base_point_y_;
    vertex_member_at<position>(vertex).x = x * cos_ - y * sin_ + base_point_x_;
    vertex_member_at<position>(vertex).y = x * sin_ + y * cos_ + base_point_y_;
    return vertex;
  }

 private:
  const float base_point_x_;
  const float base_point_y_;
  const float cos_;
  const float sin_;
};

template <typename Drawable>
struct rotated_adaptor : public drawable_adaptor<rotated_adaptor<Drawable>, Drawable> {
  template <typename BasePoint>
  rotated_adaptor(const Drawable &drawable, const BasePoint &base_point, const float angle)
      : drawable_adaptor<rotated_adaptor<Drawable>, Drawable>(drawable), 
        rotate_(base_point.x(drawable), base_point.y(drawable), angle) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), rotate_);
  }

  const transform_rotate rotate_;

  friend class adaptor_access;
};

template <typename Drawable, typename BasePoint>
rotated_adaptor<Drawable> make_rotated(const Drawable &drawable, const BasePoint &base_point, const float angle) {
  return rotated_adaptor<Drawable>(drawable, base_point, angle);
}

template <typename BasePoint>
struct rotated_t : public adaptor::base<rotated_t<BasePoint>> {
  explicit rotated_t(const BasePoint &base_point, const float angle) : base_point_(base_point), angle_(angle) {}

  template <typename Drawable>
  rotated_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_rotated(drawable, base_point_, angle_);
  }

 private:
  const BasePoint base_point_;
  const float angle_;
};

template <typename BasePoint>
rotated_t<BasePoint> rotated(const BasePoint &base_point, const float angle) {
  return rotated_t<BasePoint>(base_point, angle);
}
}}
