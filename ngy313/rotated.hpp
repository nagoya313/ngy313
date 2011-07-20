#ifndef NGY313_ROTATED_HPP_
#define NGY313_ROTATED_HPP_

#include <cmath>
#include <boost/range/algorithm/transform.hpp>
#include <ngy313/adaptor.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/shape_position.hpp>
#include <ngy313/vector.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/pipe_operator.hpp>

namespace ngy313 { namespace rotated_adaptor { namespace detail {
struct transformed {
  transformed(const vector2 &base_point, const float angle)
      : base_point_(base_point),
        cos_(std::cos(angle)),
        sin_(std::sin(angle)) {}

  template <typename Vertex>
  Vertex operator ()(Vertex vertex) const {
    const float x = vertex_member_at<position_member>(vertex).x_ -
    		             base_point_.get_x();
    const float y = vertex_member_at<position_member>(vertex).y_ -
    		             base_point_.get_y();
    vertex_member_at<position_member>(vertex).x_ = x * cos_ -
    		                                            y * sin_ +
    		                                            base_point_.get_x();
    vertex_member_at<position_member>(vertex).y_ = x * sin_ +
    		                                            y * cos_ +
    		                                            base_point_.get_y();
    return vertex;
  }

 private:
  vector2 base_point_;
  float cos_;
  float sin_;
};

template <typename Drawable>
struct adaptor : drawable_adaptor<adaptor<Drawable>, Drawable> {
  template <typename BasePoint>
  adaptor(const Drawable &drawable,
          const BasePoint &base_point,
          const float angle)
      : adaptor::drawable_adaptor(drawable),
        rotate_(vector2(base_point.x(drawable),
        		              base_point.y(drawable)), angle) {}

  void transform(typename Drawable::vertex_array_type &vertex) const {
    boost::transform(vertex, vertex.begin(), rotate_);
  }

 private:
  const transformed rotate_;
};
}}}

namespace ngy313 { namespace rotated_adaptor {
template <typename Drawable, typename BasePoint>
detail::adaptor<Drawable> make_rotated(const Drawable &drawable,
		                                    const BasePoint &base_point,
		                                    const float angle) {
  return detail::adaptor<Drawable>(drawable, base_point, angle);
}

template <typename BasePoint>
struct rotated_t : pipe_operator::base<rotated_t<BasePoint>> {
  explicit rotated_t(const BasePoint &base_point, const float angle)
  		 : base_point_(base_point), angle_(angle) {}

  template <typename Drawable>
  detail::adaptor<Drawable> operator ()(const Drawable &drawable) const {
    return make_rotated(drawable, base_point_, angle_);
  }

 private:
  BasePoint base_point_;
  float angle_;
};

template <typename BasePoint>
rotated_t<BasePoint> rotated(const BasePoint &base_point, const float angle) {
  return rotated_t<BasePoint>(base_point, angle);
}
}}

namespace ngy313 {
using rotated_adaptor::make_rotated;
using rotated_adaptor::rotated;
}

#endif
