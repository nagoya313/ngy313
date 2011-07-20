#ifndef NGY313_EXTENDED_HPP_
#define NGY313_EXTENDED_HPP_

#include <boost/range/algorithm/transform.hpp>
#include <ngy313/adaptor.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/vector.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/pipe_operator.hpp>

namespace ngy313 { namespace extended_adaptor { namespace detail {
struct transformed {
  explicit transformed(const vector2 &base_point,
                     const vector2 &extend)
      : base_point_(base_point), extend_(extend) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    vertex_member_at<position_member>(vertex).x_ =
        extend_position(vertex_member_at<position_member>(vertex).x_,
        		              base_point_.x(), extend_.x());
    vertex_member_at<position_member>(vertex).y_ =
        extend_position(vertex_member_at<position_member>(vertex).y_,
        		              base_point_.y(), extend_.y());
    return vertex;
  }

 private:
  static float extend_position(const float pos, const float base, const float extend) {
    return (pos - base) * extend + base;
  }

  vector2 base_point_;
  vector2 extend_;
};

template <typename Drawable>
struct adaptor : drawable_adaptor<adaptor<Drawable>, Drawable> {
  template <typename BasePoint>
  explicit adaptor(const Drawable &drawable, 
                   const BasePoint &base_point,
                   const vector2 &extend)
      : adaptor::drawable_adaptor(drawable), 
        extend_(vector2(base_point.x(drawable), base_point.y(drawable)), extend) {}

  template <typename VertexArray>
  void transform(VertexArray &vertex) const {
    boost::transform(vertex, vertex.begin(), extend_);
  }

 private:
  const transformed extend_;
};
}}}

namespace ngy313 { namespace extended_adaptor {
template <typename Drawable, typename BasePoint>
detail::adaptor<Drawable> make_extended(const Drawable &drawable,
                                        const BasePoint &base_point,
                                        const vector2 &extend) {
  return detail::adaptor<Drawable>(drawable, base_point, extend);
}

template <typename BasePoint>
struct extended_t : pipe_operator::base<extended_t<BasePoint>> {
  explicit extended_t(const BasePoint &base_point, const vector2 &extend)
      : base_point_(base_point), extend_(extend) {}

  template <typename Drawable>
  detail::adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_extended(drawable, base_point_, extend_);
  }

 private:
  BasePoint base_point_;
  vector2 extend_;
};

template <typename BasePoint>
extended_t<BasePoint> extended(const BasePoint &base_point,
		                            const vector2 &extend) {
  return extended_t<BasePoint>(base_point, extend);
}
}}

namespace ngy313 {
using extended_adaptor::make_extended;
using extended_adaptor::extended;
}

#endif
