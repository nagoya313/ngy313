#ifndef NGY313_GRAPHIC_DETAIL_ADD_POSITION_HPP_
#define NGY313_GRAPHIC_DETAIL_ADD_POSITION_HPP_
#include <ngy313/graphic/fvf_traits.hpp>

namespace ngy313 { namespace graphic { namespace detail {
const struct add_position_x_t {
  template <typename Vertex>
  float operator ()(const float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<position>(vertex).x;
  }
} add_position_x = {};

const struct add_position_y_t {
  template <typename Vertex>
  float operator ()(const float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<position>(vertex).y;
  }
} add_position_y = {};

const struct add_position_z_t {
  template <typename Vertex>
  float operator ()(const float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<position>(vertex).z;
  }
} add_position_z = {};

template <std::size_t Index>
struct add_position_u_t {
  template <typename Vertex>
  float operator ()(const float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<tex>(vertex).tex_array[Index].u;
  }
};

const add_position_u_t<0> add_position_u_0 = {};
const add_position_u_t<1> add_position_u_1 = {};

template <std::size_t Index>
struct add_position_v_t {
  template <typename Vertex>
  float operator ()(const float lhs, const Vertex &vertex) const {
    return lhs + vertex_member_at<tex>(vertex).tex_array[Index].v;
  }
};

const add_position_v_t<0> add_position_v_0 = {};
const add_position_v_t<1> add_position_v_1 = {};
}}}

#endif
