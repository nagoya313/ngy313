#pragma once
#include "detail/shape_position.hpp"
#include "drawable_adaptor.hpp"

namespace ngy313 { namespace detail {
struct uv_extend_position : public argument_result {
  template <typename Drawable, typename BasePoint>
  uv_extend_position(const Drawable &drawable, const BasePoint &base_point, const float extend_x, const float extend_y)
      : base_point_x_(base_point.x(drawable)),
        base_point_y_(base_point.y(drawable)),
        extend_x_(extend_x), 
        extend_y_(extend_y) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<tex_t<1>>(vertex).tex[0].u = extend_position_impl(vertex_member_at<tex_t<1>>(vertex).tex[0].u, 
                                                                       base_point_x_, 
                                                                       extend_x_);
    vertex_member_at<tex_t<1>>(vertex).tex[0].v = extend_position_impl(vertex_member_at<tex_t<1>>(vertex).tex[0].v, 
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

template <typename Drawable>
struct uv_extended_adaptor : public all_vertex_adaptor<Drawable> {
  template <typename BasePoint>
  uv_extended_adaptor(const Drawable &drawable, const BasePoint &base_point, const float extend_x, const float extend_y)
      : all_vertex_adaptor(drawable,
                           pstade::oven::transformed(uv_extend_position(drawable, base_point, extend_x, extend_y))) {}
};

template <typename BasePoint>
struct uv_extended_t : public adaptor_result<uv_extended_adaptor> {
  uv_extended_t(const BasePoint base_point, const float extend_x, const float extend_y)
      : base_point_(base_point), extend_x_(extend_x), extend_y_(extend_y) {}

  template <typename Drawable>
  uv_extended_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return uv_extended_adaptor<Drawable>(drawable, base_point_, extend_x_, extend_y_);
  }

 private:
  const BasePoint base_point_;
  const float extend_x_;
  const float extend_y_;
};

template <typename BasePoint>
uv_extended_t<BasePoint> uv_extended(const BasePoint base_point, const float extend_x, const float extend_y) {
  return uv_extended_t<BasePoint>(base_point, extend_x, extend_y);
}
}}

namespace ngy313 {
using detail::uv_extended;
}