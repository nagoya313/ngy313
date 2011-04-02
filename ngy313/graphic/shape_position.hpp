#ifndef NGY313_GRAPHIC_SHAPE_POSITION_HPP_
#define NGY313_GRAPHIC_SHAPE_POSITION_HPP_
#include <boost/mpl/at.hpp>
#include <boost/range/numeric.hpp>
#include <ngy313/graphic/detail/key.hpp>
#include <ngy313/graphic/drawable_access.hpp>
#include <ngy313/graphic/fvf_traits.hpp>
#include <ngy313/graphic/vertex_member.hpp>

namespace ngy313 { namespace graphic {
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

struct position_x {};
struct position_y {};
struct position_z {};
struct tex_u {};
struct tex_v {};

template <typename Positon>
struct shape_position;

template <>
struct shape_position<position_x> {
  template <typename Drawable>
  static float at(const Drawable &drawable, const std::size_t at) {
    return vertex_member_at<position>(drawable_access::copy_vertex(drawable)[at]).x;
  }
};

template <>
struct shape_position<position_y> {
  template <typename Drawable>
  static float at(const Drawable &drawable, const std::size_t at) {
    return vertex_member_at<position>(drawable_access::copy_vertex(drawable)[at]).y;
  }
};

template <>
struct shape_position<tex_u> {
  template <typename Drawable, std::size_t Index>
  static float at(const Drawable &drawable, const std::size_t at) {
    return vertex_member_at<tex>(drawable_access::copy_vertex(drawable)[at]).tex_array[Index].u;
  }
};

template <>
struct shape_position<tex_v> {
  template <typename Drawable, std::size_t Index>
  static float at(const Drawable &drawable, const std::size_t at) {
    return vertex_member_at<tex>(drawable_access::copy_vertex(drawable)[at]).tex_array[Index].v;
  }
};

template <typename Drawable>
float shape_center_x(const Drawable &drawable) {
  return boost::accumulate(drawable_access::copy_vertex(drawable), 0.f, add_position_x) / 
         static_cast<float>(boost::mpl::at<typename Drawable::list_type, detail::size_key>::type::type::value);
}

template <typename Drawable>
float shape_center_y(const Drawable &drawable) {
  return boost::accumulate(drawable_access::copy_vertex(drawable), 0.f, add_position_y) / 
         static_cast<float>(boost::mpl::at<typename Drawable::list_type, detail::size_key>::type::type::value);
}

template <std::size_t Index, typename Drawable>
float shape_center_u(const Drawable &drawable) {
  return boost::accumulate(drawable_access::copy_vertex(drawable), 0.f, add_position_u_t<Index>()) / 
         static_cast<float>(boost::mpl::at<typename Drawable::list_type, detail::size_key>::type::type::value);
}

template <std::size_t Index, typename Drawable>
float shape_center_v(const Drawable &drawable) {
  return boost::accumulate(drawable_access::copy_vertex(drawable), 0.f, add_position_v_t<Index>()) / 
         static_cast<float>(boost::mpl::at<typename Drawable::list_type, detail::size_key>::type::type::value);
}

template <typename Position>
struct base_position {};

template <>
struct base_position<position_x> {
  template <typename Drawable, typename Base>
  static float at(const Drawable &drawable, const Base &base) {
    return base.x(drawable);
  }
};

template <>
struct base_position<position_y> {
  template <typename Drawable, typename Base>
  static float at(const Drawable &drawable, const Base &base) {
    return base.y(drawable);
  }
};

template <>
struct base_position<tex_u> {
  template <std::size_t Index, typename Drawable, typename Base>
  static float at(const Drawable &drawable, const Base &base) {
    return base.u<Index>(drawable);
  }
};

template <>
struct base_position<tex_v> {
  template <std::size_t Index, typename Drawable, typename Base>
  static float at(const Drawable &drawable, const Base &base) {
    return base.v<Index>(drawable);
  }
};

inline
float extend_position(const float pos, const float base, const float extend) {
  return (pos - base) * extend + base;
}

template <typename Position>
struct extend_position_selecter {};

template <>
struct extend_position_selecter<position_x> {
  template <typename Vertex>
  static void transform(Vertex &vertex, const float base, const float extend) {
    vertex_member_at<position>(vertex).x = (vertex_member_at<position>(vertex).x - base) * extend + base;
  }
};

template <>
struct extend_position_selecter<position_y> {
  template <typename Vertex>
  static void transform(Vertex &vertex, const float base, const float extend) {
    vertex_member_at<position>(vertex).y = (vertex_member_at<position>(vertex).y - base) * extend + base;
  }
};

template <>
struct extend_position_selecter<tex_u> {
  template <std::size_t Index, typename Vertex>
  static void transform(Vertex &vertex, const float base, const float extend) {
    vertex_member_at<tex>(vertex).tex_array[Index].u = 
        (vertex_member_at<tex>(vertex).tex_array[Index].u - base) * extend + base;
  }
};

template <>
struct extend_position_selecter<tex_v> {
  template <std::size_t Index, typename Vertex>
  static void transform(Vertex &vertex, const float base, const float extend) {
    vertex_member_at<tex>(vertex).tex_array[Index].v = 
        (vertex_member_at<tex>(vertex).tex_array[Index].v - base) * extend + base;
  }
};
}}

#endif
