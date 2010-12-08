#pragma once
#include "detail/shape_position.hpp"
#include "drawable_adaptor.hpp"
#include "vector.hpp"

namespace ngy313 { namespace detail {
template <std::size_t Dimension>
struct extend_position : public argument_result {
  static_assert(Dimension == 2 || Dimension == 3, "");

  typedef typename boost::mpl::if_c<Dimension == 2, vector2, vector3>::type vector_type;
  typedef typename boost::mpl::if_c<Dimension == 2, rhw_position_t, position_t>::type position_type;

  template <typename Drawable, typename BasePoint>
  extend_position(const Drawable &drawable, const BasePoint &base_point, const vector_type &extend)
      : base_point_(base_point.pos(drawable)), extend_(extend) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    vertex_member_at<position_type>(vertex).pos = extend_position_impl(vertex_member_at<position_type>(vertex).pos, 
                                                                       base_point_, 
                                                                       extend_);
    return vertex;
  }

 private:
  const vector_type base_point_;
  const vector_type extend_;
};

template <typename Drawable>
struct extended_adaptor : public all_vertex_adaptor<Drawable> {
  template <typename BasePoint>
  extended_adaptor(const Drawable &drawable, const BasePoint &base_point, const Vector &extend)
      : all_vertex_adaptor(drawable, pstade::oven::transformed(extend_position(drawable, base_point, extend))) {}
};

template <typename BasePoint, typename Vector>
struct extended_t : public adaptor_result<extended_adaptor> {
  extended_t(const BasePoint &base_point, const Vector &extend) : base_point_(base_point), extend_(extend) {}

  template <typename Drawable>
  extended_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return extended_adaptor<Drawable>(drawable, base_point_, extend_);
  }

 private:
  const BasePoint base_point_;
  const Vector extend_;
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


template <typename BasePoint, typename Vector>
extended_t<BasePoint, Vector> extended(const BasePoint &base_point, const Vector &extend) {
  return extended_t<BasePoint, Vector>(base_point, extend);
}
}}

namespace ngy313 {
using detail::extended;
}