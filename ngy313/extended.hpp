#pragma once
#include "detail/shape_position.hpp"
#include "drawable_adaptor.hpp"

namespace ngy313 { namespace detail {
struct extend_position : public argument_result {
  template <typename Drawable, typename BasePoint>
  extend_position(const Drawable &drawable, const BasePoint &base_point, const float extend_x, const float extend_y)
      : base_point_x_(base_point.x(drawable)),
        base_point_y_(base_point.y(drawable)),
        extend_x_(extend_x), 
        extend_y_(extend_y) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<rhw_position_t>(vertex).x = extend_position_impl(vertex_member_at<rhw_position_t>(vertex).x, 
                                                                      base_point_x_, 
                                                                      extend_x_);
    vertex_member_at<rhw_position_t>(vertex).y = extend_position_impl(vertex_member_at<rhw_position_t>(vertex).y, 
                                                                      base_point_y_, 
                                                                      extend_y_);
    return vertex;
  }

 private:
  const float base_point_x_;
  const float base_point_y_;
  const float extend_x_;
  const float extend_y_;
};

struct extend_position3d : public argument_result {
  template <typename Drawable, typename BasePoint>
  extend_position3d(const Drawable &drawable,
                  const BasePoint &base_point,
                  const float extend_x,
                  const float extend_y,
                  const float extend_z)
      : base_point_x_(base_point.x(drawable)),
        base_point_y_(base_point.y(drawable)),
        base_point_z_(base_point.z(drawable)),
        extend_x_(extend_x), 
        extend_y_(extend_y),
        extend_z_(extend_z) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<position_t>(vertex).x = extend_position_impl(vertex_member_at<position_t>(vertex).x, 
                                                                  base_point_x_, 
                                                                  extend_x_);
    vertex_member_at<position_t>(vertex).y = extend_position_impl(vertex_member_at<position_t>(vertex).y, 
                                                                  base_point_y_, 
                                                                  extend_y_);
    vertex_member_at<position_t>(vertex).z = extend_position_impl(vertex_member_at<position_t>(vertex).z, 
                                                                  base_point_z_, 
                                                                  extend_z_);
    return vertex;
  }

 private:
  const float base_point_x_;
  const float base_point_y_;
  const float base_point_z_;
  const float extend_x_;
  const float extend_y_;
  const float extend_z_
};

template <typename Drawable>
struct extended_adaptor : public all_vertex_adaptor<Drawable> {
  template <typename BasePoint>
  extended_adaptor(const Drawable &drawable, const BasePoint &base_point, const float extend_x, const float extend_y)
      : all_vertex_adaptor(drawable,
                           pstade::oven::transformed(extend_position(drawable, base_point, extend_x, extend_y))) {}

  template <typename BasePoint>
  extended_adaptor(const Drawable &drawable,
                   const BasePoint &base_point,
                   const float extend_x, 
                   const float extend_y,
                   const float extend_z)
      : all_vertex_adaptor(drawable,
                           pstade::oven::transformed(extend_position3d(drawable,
                                                                       base_point,
                                                                       extend_x,
                                                                       extend_y,
                                                                       extend_z))) {}
};

template <typename BasePoint>
struct extended_t : public adaptor_result<extended_adaptor> {
  extended_t(const BasePoint &base_point, const float extend_x, const float extend_y)
      : base_point_(base_point), extend_x_(extend_x), extend_y_(extend_y) {}

  template <typename Drawable>
  extended_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return extended_adaptor<Drawable>(drawable, base_point_, extend_x_, extend_y_);
  }

 private:
  const BasePoint base_point_;
  const float extend_x_;
  const float extend_y_;
};

template <typename BasePoint>
struct extended3d_t : public adaptor_result<extended_adaptor> {
  extended3d_t(const BasePoint &base_point, const float extend_x, const float extend_y, const float extend_z)
      : base_point_(base_point), extend_x_(extend_x), extend_y_(extend_y), extend_z_(extend_z) {}

  template <typename Drawable>
  extended_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return extended_adaptor<Drawable>(drawable, base_point_, extend_x_, extend_y_, extend_z_);
  }

 private:
  const BasePoint base_point_;
  const float extend_x_;
  const float extend_y_;
  const float extend_z_;
};


template <typename BasePoint>
extended_t<BasePoint> extended(const BasePoint &base_point, const float extend_x, const float extend_y) {
  return extended_t<BasePoint>(base_point, extend_x, extend_y);
}

template <typename BasePoint>
extended3d_t<BasePoint> extended(const BasePoint &base_point,
                                 const float extend_x,
                                 const float extend_y,
                                 const float extend_z) {
  return extended3d_t<BasePoint>(base_point, extend_x, extend_y, extend_z);
}
}}

namespace ngy313 {
using detail::extended;
}