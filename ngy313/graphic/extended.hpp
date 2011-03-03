#pragma once
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/graphic/adaptor.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/shape_position.hpp>
#include <ngy313/graphic/vertex_member.hpp>
#include <ngy313/utility/pipe_operator.hpp>

namespace ngy313 { namespace graphic {
#pragma warning(disable: 4512)

struct transform_extend {
  transform_extend(const float base_point_x, const float base_point_y, const float extend) 
      : base_point_x_(base_point_x), base_point_y_(base_point_y), extend_(extend) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<position>(vertex).x = extend_position(vertex_member_at<position>(vertex).x, 
                                                           base_point_x_, 
                                                           extend_);
    vertex_member_at<position>(vertex).y = extend_position(vertex_member_at<position>(vertex).y, 
                                                           base_point_y_, 
                                                           extend_);
    return vertex;
  }

 private:
  const float base_point_x_;
  const float base_point_y_;
  const float extend_;
};

template <typename Drawable>
struct extended_adaptor : public drawable_adaptor<extended_adaptor<Drawable>, Drawable> {
  template <typename BasePoint>
  extended_adaptor(const Drawable &drawable, const BasePoint &base_point, const float extend)
      : drawable_adaptor<extended_adaptor<Drawable>, Drawable>(drawable), 
        extend_(base_point.x(drawable), base_point.y(drawable), extend) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), extend_);
  }

  const transform_extend extend_;

  friend class adaptor_access;
};

#pragma warning(default: 4512)

template <typename Drawable, typename BasePoint>
extended_adaptor<Drawable> make_extended(const Drawable &drawable, const BasePoint &base_point, const float extend) { 
  return extended_adaptor<Drawable>(drawable, base_point, extend);
}

#pragma warning(disable: 4512)

template <typename BasePoint>
struct extended_t : public utility::pipe_operator::base<extended_t<BasePoint>> {
  extended_t(const BasePoint &base_point, const float extend) : base_point_(base_point), extend_(extend) {}

  template <typename Drawable>
  extended_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_extended(drawable, base_point_, extend_);
  }

 private:
  const BasePoint base_point_;
  const float extend_;
};

#pragma warning(default: 4512)

template <typename BasePoint>
extended_t<BasePoint> extended(const BasePoint &base_point, const float extend) {
  return extended_t<BasePoint>(base_point, extend);
}

#pragma warning(disable: 4512)

template <typename Position>
struct transform_extend_one {
  transform_extend_one(const float base_point, const float extend) : base_point_(base_point), extend_(extend) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    extend_position_selecter<Position>::transform(vertex, base_point_, extend_);
    return vertex;
  }

 private:
  const float base_point_;
  const float extend_;
};

template <typename Position, typename Drawable>
struct extended_one_adaptor : public drawable_adaptor<extended_one_adaptor<Position, Drawable>, Drawable> {
  template <typename BasePoint>
  extended_one_adaptor(const Drawable &drawable, const BasePoint &base_point, const float extend)
      : drawable_adaptor<extended_one_adaptor<Position, Drawable>, Drawable>(drawable),  
        extend_(base_position<Position>::at(drawable, base_point), extend) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), extend_);
  }

  const transform_extend_one<Position> extend_;

  friend class adaptor_access;
};

#pragma warning(default: 4512)

template <typename Position, typename Drawable, typename BasePoint>
extended_one_adaptor<Position, Drawable> make_extended_one(const Drawable &drawable,
                                                           const BasePoint &base_point,
                                                           const float extend) {
  return extended_one_adaptor<Position, Drawable>(drawable, base_point, extend);
}

template <typename Drawable, typename BasePoint>
extended_one_adaptor<position_x, Drawable> make_extended_x(const Drawable &drawable, 
                                                           const BasePoint &base_point,
                                                           const float extend) {
  return make_extended_one<position_x>(drawable, base_point, extend);
}

template <typename Drawable, typename BasePoint>
extended_one_adaptor<position_y, Drawable> make_extended_y(const Drawable &drawable, 
                                                           const BasePoint &base_point,
                                                           const float extend) {
  return make_extended_one<position_y>(drawable, base_point, extend);
}

#pragma warning(disable: 4512)

template <typename BasePoint, typename Position>
struct extended_one_t : public utility::pipe_operator::base<extended_one_t<BasePoint, Position>> {
  extended_one_t(const BasePoint &base_point, const float extend)
      : base_point_(base_point), extend_(extend) {}

  template <typename Drawable>
  extended_one_adaptor<Position, Drawable> operator ()(const Drawable &drawable) const {
    return make_extended_one<Position>(drawable, base_point_, extend_);
  }

 private:
  const BasePoint base_point_;
  const float extend_;
};

#pragma warning(default: 4512)

template <typename BasePoint>
extended_one_t<BasePoint, position_x> extended_x(const BasePoint &base_point, const float extend) {
  return extended_one_t<BasePoint, position_x>(base_point, extend);
}

template <typename BasePoint>
extended_one_t<BasePoint, position_y> extended_y(const BasePoint &base_point, const float extend) {
  return extended_one_t<BasePoint, position_y>(base_point, extend);
}

#pragma warning(disable: 4512)

struct transform_extend_xy {
  transform_extend_xy(const float base_point_x,
                      const float base_point_y,
                      const float extend_x,
                      const float extend_y) 
      : base_point_x_(base_point_x), base_point_y_(base_point_y), extend_x_(extend_x), extend_y_(extend_y) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<position>(vertex).x = extend_position(vertex_member_at<position>(vertex).x, 
                                                           base_point_x_, 
                                                           extend_x_);
    vertex_member_at<position>(vertex).y = extend_position(vertex_member_at<position>(vertex).y, 
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
struct extended_xy_adaptor : public drawable_adaptor<extended_xy_adaptor<Drawable>, Drawable> {
  template <typename BasePoint>
  extended_xy_adaptor(const Drawable &drawable, 
                      const BasePoint &base_point,
                      const float extend_x,
                      const float extend_y)
      : drawable_adaptor<extended_xy_adaptor<Drawable>, Drawable>(drawable), 
        extend_(base_point.x(drawable), base_point.y(drawable), extend_x, extend_y) {}

 private:
  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), extend_);
  }

  const transform_extend_xy extend_;

  friend class adaptor_access;
};

#pragma warning(default: 4512)

template <typename Drawable, typename BasePoint>
extended_xy_adaptor<Drawable> make_extended_xy(const Drawable &drawable,
                                               const BasePoint &base_point,
                                               const float extend_x, 
                                               const float extend_y) {
  return extended_xy_adaptor<Drawable>(drawable, base_point, extend_x, extend_y);
}

#pragma warning(disable: 4512)

template <typename BasePoint>
struct extended_xy_t : public utility::pipe_operator::base<extended_xy_t<BasePoint>> {
  extended_xy_t(const BasePoint &base_point, const float extend_x, const float extend_y)
      : base_point_(base_point), extend_x_(extend_x), extend_y_(extend_y) {}

  template <typename Drawable>
  extended_xy_adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_extended_xy(drawable, base_point_, extend_x_, extend_y_);
  }

 private:
  const BasePoint base_point_;
  const float extend_x_;
  const float extend_y_;
};

#pragma warning(default: 4512)

template <typename BasePoint>
extended_xy_t<BasePoint> extended_xy(const BasePoint &base_point, const float extend_x, const float extend_y) {
  return extended_xy_t<BasePoint>(base_point, extend_x, extend_y);
}
}}
