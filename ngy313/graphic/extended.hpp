#ifndef NGY313_GRAPHIC_EXTENDED_HPP_
#define NGY313_GRAPHIC_EXTENDED_HPP_
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/graphic/detail/extend_position.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/shape_position.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/utility/nonsubstitutiable.hpp>
#include <ngy313/utility/pipe_operator.hpp>

namespace ngy313 { namespace graphic {
struct transform_extend : private utility::nonsubstitutiable {
  transform_extend(const float base_point_x,
                   const float base_point_y,
                   const float extend_x,
                   const float extend_y) 
      : base_point_x_(base_point_x), base_point_y_(base_point_y), extend_x_(extend_x), extend_y_(extend_y) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<position>(vertex).x = 
        detail::extend_position(vertex_member_at<position>(vertex).x, base_point_x_, extend_x_);
    vertex_member_at<position>(vertex).y = 
        detail::extend_position(vertex_member_at<position>(vertex).y, base_point_y_, extend_y_);
    return vertex;
  }

 private:
  const float base_point_x_;
  const float base_point_y_;
  const float extend_x_;
  const float extend_y_;
};

template <typename Drawable>
struct extended_adaptor : public drawable_adaptor<extended_adaptor<Drawable>, Drawable>,
                          private utility::nonsubstitutiable {
  template <typename BasePoint>
  extended_adaptor(const Drawable &drawable, 
                   const BasePoint &base_point,
                   const float extend_x,
                   const float extend_y)
      : extended_adaptor::drawable_adaptor(drawable), 
        extend_(base_point.x(drawable), base_point.y(drawable), extend_x, extend_y) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), extend_);
  }

  const transform_extend extend_;

  friend class adaptor_access;
};

template <typename Drawable, typename BasePoint>
extended_adaptor<Drawable> make_extended(const Drawable &drawable,
                                         const BasePoint &base_point,
                                         const float extend_x, 
                                         const float extend_y) {
  return extended_adaptor<Drawable>(drawable, base_point, extend_x, extend_y);
}

template <typename BasePoint>
struct extended_t : public utility::pipe_operator::base<extended_t<BasePoint>>,
                   private utility::nonsubstitutiable {
  extended_t(const BasePoint &base_point, const float extend_x, const float extend_y)
      : base_point_(base_point), extend_x_(extend_x), extend_y_(extend_y) {}

  template <typename Drawable>
  extended_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_extended(drawable, base_point_, extend_x_, extend_y_);
  }

 private:
  const BasePoint base_point_;
  const float extend_x_;
  const float extend_y_;
};

template <typename BasePoint>
extended_t<BasePoint> extended(const BasePoint &base_point, const float extend_x, const float extend_y) {
  return extended_t<BasePoint>(base_point, extend_x, extend_y);
}
}}

#endif
