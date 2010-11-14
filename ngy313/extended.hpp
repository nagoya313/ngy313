#include "drawable_filter_adaptor.hpp"

namespace ngy313 { namespace detail {
inline
float extend_position_impl(const float pos, 
                           const float base, 
                           const float extend) {
  return (pos - base) * extend + base;
}

struct extend_position : public copy_argument_base {
  extend_position(const float base_point_x,
                  const float base_point_y,
                  const float extend_x,
                  const float extend_y)
      : base_point_x_(base_point_x),
        base_point_y_(base_point_y),
        extend_x_(extend_x), 
        extend_y_(extend_y) {}

  template <typename Vertex>
  Vertex &operator ()(Vertex &vertex) const {
    member_at<rhw_position_t>(vertex).x = 
        extend_position_impl(member_at<rhw_position_t>(vertex).x, 
                             base_point_x_, 
                             extend_x_);
    member_at<rhw_position_t>(vertex).y = 
        extend_position_impl(member_at<rhw_position_t>(vertex).y, 
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
struct extended_filter : public all_vertex_drawable_filter_adaptor<Drawable> {
  extended_filter(const Drawable &drawable, 
                  const float base_point_x,
                  const float base_point_y,
                  const float extend_x,
                  const float extend_y)
      : all_vertex_drawable_filter_adaptor(
            drawable,
            pstade::oven::transformed(extend_position(base_point_x,
                                                      base_point_y,
                                                      extend_x, 
                                                      extend_y))) {}
};

struct extended : public filtered_base<extended_filter> {
  extended(const float base_point_x,
           const float base_point_y,
           const float extend_x,
           const float extend_y)
      : base_point_x_(base_point_x),
        base_point_y_(base_point_y),
        extend_x_(extend_x), 
        extend_y_(extend_y) {}

  template <typename Drawable>
  extended_filter<Drawable> operator ()(const Drawable &drawable) const {
    return extended_filter<Drawable>(drawable, 
                                     base_point_x_,
                                     base_point_y_,
                                     extend_x_, 
                                     extend_y_);
  }

 private:
  const float base_point_x_;
  const float base_point_y_;
  const float extend_x_;
  const float extend_y_;
};
}}

namespace ngy313 {
using detail::extended;
}