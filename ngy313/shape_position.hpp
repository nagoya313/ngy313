#ifndef NGY313_SHAPE_POSITION_HPP_
#define NGY313_SHAPE_POSITION_HPP_

#include <cstddef>
#include <boost/mpl/at.hpp>
#include <boost/range/numeric.hpp>
#include <ngy313/fvf_traits.hpp>
#include <ngy313/vertex_member.hpp>
#include <ngy313/detail/drawable_traits.hpp>

namespace ngy313 { namespace detail {
const struct add_position_x_t {
  template <typename Vertex>
  float operator ()(float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<position_member>(vertex).x_;
  }
} add_position_x = {};

const struct add_position_y_t {
  template <typename Vertex>
  float operator ()(float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<position_member>(vertex).y_;
  }
} add_position_y = {};

const struct add_position_z_t {
  template <typename Vertex>
  float operator ()(float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<position_member>(vertex).z_;
  }
} add_position_z = {};
}}

namespace ngy313 {
template <typename Drawable>
float shape_position_x(const Drawable &drawable, std::size_t at) {
  return vertex_member_at<position_member>(drawable.vertex()[at]).x_;
}

template <typename Drawable>
float shape_position_y(const Drawable &drawable, std::size_t at) {
  return vertex_member_at<position_member>(drawable.vertex()[at]).y_;
}

template <typename Drawable>
float shape_center_x(const Drawable &drawable) {
  return boost::accumulate(drawable.vertex(), 0.f, detail::add_position_x) /
      static_cast<float>(boost::mpl::at<
      		                     typename Drawable::list_type,
      		                     detail::size_key>::type::type::value);
}

template <typename Drawable>
float shape_center_y(const Drawable &drawable) {
  return boost::accumulate(drawable.vertex(), 0.f, detail::add_position_y) /
       static_cast<float>(boost::mpl::at<
     		                      typename Drawable::list_type,
     		                      detail::size_key>::type::type::value);
}
}

#endif
